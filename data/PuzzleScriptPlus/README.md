Puzzlescript Plus is a fork of [Puzzlescript by Increpare](https://github.com/increpare/PuzzleScript) that attempts to gather a number of forks I often use for my own games, while also extending the editor a bit and adding a couple of new game features. **DO NOTE that combining functionality from multiple forks is still experimental, and you could run into issues.** [Access the editor](https://auroriax.github.io/PuzzleScript/editor.html), or see the [updated documentation on the new features](https://auroriax.github.io/PuzzleScript/Documentation/documentation.html).

This repo takes Puzzlescript v1.7 and adds features like mouse controls, sprites larger than 5x5, level select, an experimental solver, and a whole lot more! This is the full list of merged forks and their authors:

## [PuzzleClick by ThatScar](https://github.com/ThatScar/PuzzleScript)
Allows you to create objects on tiles the mouse interacts with. [See README here](https://github.com/ThatScar/PuzzleScript/blob/master/README.md).

## [Marcosdon's Solver for Puzzlescript](https://github.com/marcosdon/PuzzleScriptWithSolver)
Adds a solver that will automatically attempt to beat levels and report the solution. [See README here](https://github.com/marcosdon/PuzzleScriptWithSolver/blob/master/README.md).

## [Dario Zubovic's branch](https://github.com/dario-zubovic/PuzzleScript)
Adds in variable sprite size, level selection, ability to use a base64-encoded font, and a few more things (including the [smoothscreen patch by sftrabbit](https://github.com/sftrabbit/PuzzleScript-smoothscreen)). [More info here](https://dario-zubovic.github.io/PuzzleScript/Documentation/differences.html).

## [Jack Lance's branch](https://github.com/JackLance/PuzzleScript)
This adds a single feature that is especially useful for worlds that take place on gigantic maps. You can specify the radius around the player in which rules need to be checked. You generally don't need to use this unless you have a really big level, a ton of rules, and your game would otherwise run slowly.

-------

Many more people have directly & indirectly contributed to PS+, so here's a list of everyone deserving special thanks:
- TilmannR for contributing the `goto` command
- minotalen for reporting bugs & helping write documentation
- Cel-iki/BoredMatt for helping me make code examples
- jsmiller11 for writing [psUtil](https://github.com/jcmiller11/psUtil) (that I adapted for the PS+ sprite upscaler tool)
- ClementSparrow who is making [their own cool Puzzlescript fork](https://github.com/ClementSparrow/Pattern-Script), from which I used the alternate Github authentication method!
- MinoMe/Kalixtan for contributing sprite tweening!
- And everyone that has made cool games using the tool! You can see [a list of PS+ games in the Gallery](https://auroriax.github.io/PuzzleScript/Gallery/index.html).

-------

## Branches
`master` is the current state of the engine as is currently live. While `develop` is where new features & fixes are being worked on before they go live.

## Contributing, Bug reports & Pull Requests

Want to help with reporting issues extending Puzzlescript Plus? Please note that I made this fork to help me with making cool games—although working on the engine is also fun, it's not my main focus. I'll pick up any bugs reported, but likely won't work on big feature requests, for the sake of my free time and engine stability.

**Bug reports**

If you find a bug, please report it! I'll resolve most of the bug reports, depending on the impact and severity. Please do note that the more info you can provide on the bug, the sooner you can expect it to be fixed! If the bug actually originated from any of the merged forks, I'll make sure the correct developer gets notified, so don't worry too much about that.

**Feature requests**

Generally for feature requests, I look at how *useful* a given feature is going to be and how much *time* it will cost to fully implement. Generally, I won't work on features that would take too long to implement, or are useful in only a limited number of use cases. 
If you are not sure about the scope, suggest it anyway! I might not pick up big features, but I might pick up bugs & smaller features that come out of such reports.

**Pull Requests**

PRs are a bit of a double edged sword for me— they are super fun to receive, but they always require a lot of work from me to QA before merging it in. So you are expected to adhere to the feature request rules for PRs too. Consider adding a feature request to the tracker, stating that you want to start working on a PR to implement it, so I can give you feedback & a green light before you start working on it. Otherwise, your PR might get closed without merging.

-------

The original Puzzlescript project, and the code that I added on top of it, are both available under the MIT license. See the license text below. For features from other forks, please check their individual project page links in the list above to see their licensing information.

-------

The MIT License (MIT)

Copyright (c) 2013 increpare, 2021-2022 Tom Hermans

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
