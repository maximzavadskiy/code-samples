//-------------------------------------------------- //
/*
Entity.js - 
Creates an object which other entities can pull components from
*/
//---------------------------------------------------//

(function (window) {
    "use strict";
    var Entity = {
        init: function () {
            //used to setup an entity(many used for future implementation)
            this.image = null; //image used to draw
            this.isLoaded = false;   //is Entity loaded

            this.scale = 1;          //scale to draw at
            this.pos = { x: 0, y: 0, angle: 0 }, //position of the object
            this.last = { x: 0, y: 0, angle: 0 }, //last position of object
            this.collision_radius = 0; //radius to use for collisions
        },

        update_pre: function () {
            //interpolation setup
            this.last.x = this.pos.x;
            this.last.y = this.pos.y;
            this.last.angle = this.pos.angle;
        },

        update: function () {
        },


        draw: function ()
        {
       },

        loadimg: function (path) {
            var image = new Image();
            image.src = path;
            return image;
        },

        interpolate: function (axis) {
            if (axis === 'x' || axis === 'X') {
                return this.last.x + (this.interpolate_diff.x * game.system.interpolationvalue);
            }
            else if (axis === 'y' || axis === 'Y') {
                return this.last.y + (this.interpolate_diff.y * game.system.interpolationvalue);
            }
            else {
                return this.last.angle + (this.interpolate_diff.angle * game.system.interpolationvalue);

            }
        },

        normalizevector: function (x, y) {
            "use strict";
            if (x === 0 && y === 0) //check for degenerate case
            { return { x: 0, y: 0 }; }

            //calculate length
            var length = Math.sqrt((x * x) + (y * y));
            //divide components by length
            return { x: x / length, y: y / length };
        },

        vectorlength: function (vector) {
            "use strict";
            return Math.sqrt((vector.x * vector.x) + (vector.y * vector.y));
        },
    };
    gameCtx.Entity = Entity;
})(window);

