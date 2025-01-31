#include "js.h"

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

#include "audio.h"
#include "event.h"
#include "graphics.h"
#include "pztime.h"
#include "sfxr.h"
#include "sprite.h"

#include <sstream>

namespace js {

void default_print(std::string msg)
{
    std::cout << msg << std::endl;
}

std::function<void(std::string)> debug_print{default_print};
std::function<void(std::string)> error_print{default_print};

void set_debug_print(std::function<void(std::string)> func)
{
    debug_print = func;
}

void set_error_print(std::function<void(std::string)> func)
{
    error_print = func;
}

void fatal_handler(void */*udata*/, const char *msg)
{
    std::stringstream ss;
    ss << "******* JS ERROR: " << msg << std::endl;
    ss << "FATAL, ABORTING" << std::endl;
    // Output to cerr just in case logging not setup
    std::cerr << ss.str();
    // Call error callback
    error_print(ss.str());
    // Abort...
    abort();
}

duk_ret_t native_print(duk_context *ctx)
{
	duk_push_string(ctx, " ");
	duk_insert(ctx, 0);
	duk_join(ctx, duk_get_top(ctx) - 1);
    std::string msg{duk_safe_to_string(ctx, -1)};
    // Do actual print operation
    std::stringstream ss;
	ss << msg << std::endl;
    debug_print(ss.str());
	return 0;
}

uint16_t webcolor(std::string hexcolor)
{
    std::string r;
    std::string g;
    std::string b;
    uint16_t ri{0};
    uint16_t gi{0};
    uint16_t bi{0};
    if (hexcolor.size() == 4) {
        r = hexcolor.substr(1, 1) + hexcolor.substr(1, 1);
        g = hexcolor.substr(2, 1) + hexcolor.substr(2, 1);
        b = hexcolor.substr(3, 1) + hexcolor.substr(3, 1);
    } else if (hexcolor.size() >= 7) {
        r = hexcolor.substr(1, 2);
        g = hexcolor.substr(3, 2);
        b = hexcolor.substr(5, 2);
    } else {
        throw std::invalid_argument("Illegal color");
    }
    std::stringstream sr;
    sr << std::hex << r;
    sr >> ri;
    std::stringstream sg;
    sg << std::hex << g;
    sg >> gi;
    std::stringstream sb;
    sb << std::hex << b;
    sb >> bi;
    return ((ri >> (8 - 5)) << (6 + 5)) | ((gi >> (8 - 6)) << 5) | (bi >> (8 - 5));
}

duk_ret_t native_sprite_add(duk_context *ctx)
{
    int width{duk_get_int(ctx, 0)};
    int height{duk_get_int(ctx, 1)};
    duk_push_int(ctx, sprite::add_sprite(width, height));
    return 1;
}

duk_ret_t native_sprite_clear(duk_context */*ctx*/)
{
    sprite::clear_sprites();
    return 0;
}

duk_ret_t native_fill_rect(duk_context *ctx)
{
    int id{duk_get_int(ctx, 0)};
    std::string fill{duk_safe_to_string(ctx, 1)};
    int x{duk_get_int(ctx, 2)};
    int y{duk_get_int(ctx, 3)};
    int w{duk_get_int(ctx, 4)};
    int h{duk_get_int(ctx, 5)};
    uint16_t color{webcolor(fill)};
    sprite::fill_rect(id, x, y, w, h, color);
    return 0;
}

duk_ret_t native_sprite_draw(duk_context *ctx)
{
    int dst{duk_get_int(ctx, 0)};
    int src{duk_get_int(ctx, 1)};
    int x{duk_get_int(ctx, 2)};
    int y{duk_get_int(ctx, 3)};
    sprite::draw(dst, src, x, y);
    return 0;
}

duk_ret_t native_sprite_render(duk_context *ctx)
{
    int id{duk_get_int(ctx, 0)};
    sprite::render(id);
    return 0;
}

duk_ret_t native_sleep(duk_context *ctx)
{
    using namespace std::chrono_literals;
    double delay_s{duk_get_number(ctx, 0)};
    std::this_thread::sleep_for(1s * delay_s);
    return 0;
}

duk_ret_t native_elapsed(duk_context *ctx)
{
    duk_push_int(ctx, pztime::elapsed());
    return 1;
}

duk_ret_t native_get_width(duk_context *ctx)
{
    duk_push_int(ctx, graphics::width);
    return 1;
}

duk_ret_t native_get_height(duk_context *ctx)
{
    duk_push_int(ctx, graphics::height);
    return 1;
}

duk_ret_t native_get_event(duk_context *ctx)
{
    event::Event evt{event::pop()};
    duk_idx_t obj_idx{duk_push_object(ctx)};
    duk_push_int(ctx, evt.key);
    duk_put_prop_string(ctx, obj_idx, "key");
    duk_push_boolean(ctx, evt.isPress);
    duk_put_prop_string(ctx, obj_idx, "isPress");
    return 1;
}

duk_ret_t native_flip(duk_context */*ctx*/)
{
    graphics::flip();
    return 0;
}

duk_ret_t native_screen_fill(duk_context *ctx)
{
    std::string fill{duk_safe_to_string(ctx, 0)};
    uint16_t color{webcolor(fill)};
    graphics::fill(0, 0, graphics::width, graphics::height, color);
    return 0;
}

std::map<int, std::vector<float>> soundbank{};

duk_ret_t native_generate_sound(duk_context *ctx)
{
    int seed{duk_get_int(ctx, 0)};
    if (soundbank.find(seed) == soundbank.end()) {
        auto samps = sfxr::generate(seed);
        sfxr::lofi(samps);
        soundbank[seed] = samps;
    }
    return 0;
}

duk_ret_t native_play_sound(duk_context *ctx)
{
    int seed{duk_get_int(ctx, 0)};
    if (soundbank.find(seed) == soundbank.end()) {
        std::cerr << "Could not find sound " << seed << std::endl;
        return 0;
    }
    audio::play(soundbank[seed]);
    return 0;
}

duk_ret_t native_time_elapsed(duk_context *ctx)
{
    duk_push_number(ctx, pztime::elapsed());
    return 1;
}

Context::Context()
: ctx(duk_create_heap(nullptr, nullptr, nullptr, this, fatal_handler))
{
    // Register native functions
	duk_push_c_function(ctx, native_print, DUK_VARARGS);
	duk_put_global_string(ctx, "print");
	duk_push_c_function(ctx, native_sprite_add, 2);
	duk_put_global_string(ctx, "native_sprite_add");
	duk_push_c_function(ctx, native_sprite_clear, 0);
	duk_put_global_string(ctx, "native_sprite_clear");
	duk_push_c_function(ctx, native_fill_rect, 6);
	duk_put_global_string(ctx, "native_fill_rect");
	duk_push_c_function(ctx, native_sprite_draw, 4);
	duk_put_global_string(ctx, "native_sprite_draw");
	duk_push_c_function(ctx, native_sprite_render, 1);
	duk_put_global_string(ctx, "native_sprite_render");
    duk_push_c_function(ctx, native_sleep, 1);
    duk_put_global_string(ctx, "native_sleep");
    duk_push_c_function(ctx, native_elapsed, 0);
    duk_put_global_string(ctx, "native_elapsed");
    duk_push_c_function(ctx, native_get_width, 0);
    duk_put_global_string(ctx, "native_get_width");
    duk_push_c_function(ctx, native_get_height, 0);
    duk_put_global_string(ctx, "native_get_height");
    duk_push_c_function(ctx, native_get_event, 0);
    duk_put_global_string(ctx, "native_get_event");
    duk_push_c_function(ctx, native_flip, 0);
    duk_put_global_string(ctx, "native_flip");
    duk_push_c_function(ctx, native_screen_fill, 1);
    duk_put_global_string(ctx, "native_screen_fill");
    duk_push_c_function(ctx, native_generate_sound, 1);
    duk_put_global_string(ctx, "native_generate_sound");
    duk_push_c_function(ctx, native_play_sound, 1);
    duk_put_global_string(ctx, "native_play_sound");
    duk_push_c_function(ctx, native_time_elapsed, 0);
    duk_put_global_string(ctx, "native_time_elapsed");
}

Context::~Context()
{
    if (js_thread_active) {
        stop_thread();
    }
    duk_destroy_heap(ctx);
}

void Context::eval(std::string code, std::string filename)
{
    std::lock_guard<std::mutex> guard(mutex);
    duk_push_string(ctx, code.c_str());
    duk_push_string(ctx, filename.c_str());
    duk_compile(ctx, 0);
    if (DUK_EXEC_ERROR == duk_pcall(ctx, 0)) {
        std::cerr << "There was an error" << std::endl;
        if (duk_is_error(ctx, -1)) {
            // See if there's a stack trace. That includes the actual error message so we can use
            // that as exception message. Otherwise just get what is on stack top.
            std::string error;
            if (duk_has_prop_string(ctx, -1, "stack")) {
            duk_get_prop_string(ctx, -1, "stack"); // Puts stack trace on the stack.
                error = duk_require_string(ctx, -1);
            } else {
                error = duk_safe_to_string(ctx, -1);
            }
            duk_pop(ctx); // Remove error from stack.

            throw std::runtime_error(error);
        }
    }
    duk_pop(ctx); // remove result value
}

void Context::set(std::string name, std::string value)
{
    std::lock_guard<std::mutex> guard(mutex);
    duk_push_string(ctx, value.c_str());
    duk_put_global_string(ctx, name.c_str());
}

void Context::start_thread(std::string code, std::string filename)
{
    thread_code = code;
    thread_filename = filename;
    js_thread_active = true;
    js_thread = std::thread(&Context::thread_loop, this);
}

void Context::stop_thread()
{
    js_thread_active = false;
    js_thread.join();
}

void Context::thread_loop()
{
    while(js_thread_active) {
        eval(thread_code, thread_filename);
    }
}

} // namespace js
