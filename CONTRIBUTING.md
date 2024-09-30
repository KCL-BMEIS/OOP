# Slides

The slides are created using [remark.js](https://remarkjs.com/). There is some
documentation on the [corresponding wiki](https://github.com/gnab/remark/wiki),
though most custom formatting needs to be handled via changes to the CSS, which
is best done in the `_layouts/presentation.html` file. 

The site is put together through GitHub actions and served on GitHub Pages at
this address: https://kcl-bmeis.github.io/OOP/

You can also serve the slides locally using the `view_local` script, by
invoking e.g.:
```
./view_local week1.md
```
You should be able to click on the link to open the resuling slide show in your
browser. You can keep making changes, but remember to re-run the `view_local`
script for the changes to take effect before reloading in the browser.

Please store any images in the `images/` folder, and only use the toplevel
folder for the markdown (`.md`) files, one per slide-deck.


# Code

Code examples are stored in the `code/` folder, arranged week by week, with
each example in its own clearly-labelled folder. For single-file projects,
these should build using a simple compiler invocation, e.g.:
```
g++ -std=c++20 main.cpp -o main
```
For anything more complex, these should build using the `build` script from the
[simple_build repo](https://github.com/jdtournier/simple_build), since this is
what we will most likely be requiring the students to use. 


