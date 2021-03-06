// Javascript for HTML5i extension

function() {
    var tags = document.getElementsByTagName("canvas");

    for (var i = 0; i < tags.length; i++) {
        var canvas = tags[i];

        canvas.getContext = function (contextId) {
            if (!this[contextId]) {
                if (contextId == "2d") {
                    this[contextId] = new Context2D(arguments);
                }
                else if (contextId == "webgl" || contextId == "experimental-webgl") {
                    this[contextId] = new ContextWebGL(arguments);
                }
            }

            return this[contextId] ? this[contextId] : null;
        }
    }
}();