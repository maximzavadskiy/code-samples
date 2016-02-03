//-------------------------------------------------- //
/*
Obstacle.js - 
Creates an Obstacle entity.  This object is mainly controlled by a path system using target points.
Uses a simple statemachine to control behaivor
*/
//---------------------------------------------------//
 var Obstacle = function () {

     this.init = function () {
            this.image = null; //image used to draw
            this.isLoaded = false;   //is Entity loaded
            this.state = null;       //current state of the object

            this.scale = 1;          //scale to draw at
            this.pos = { x: 0, y: 0, angle: 0 }, //position of the object
            this.last = { x: 0, y: 0, angle: 0 }, //last position of object
            this.interpolate_diff = { x: 0, y: 0, angle: 0 }; //difference between last and current position
            this.collision_radius = 0; //radius to use for collisions

            this.type = 'obstacle';


            this.vel = { x: 10, y: 5, angle: 0 };
            this.collision_radius = 45;

            this.state = 'loading';

            this.image = game.Entity.loadimg('media/hikers_lores.png');
        };


        this.update = function () {
            game.Entity.update_pre.apply(this, null);
            game.Entity.update_post.apply(this, null);

            
            var normalizedvector = game.Entity.normalizevector(Math.round(targetvector.x), Math.round(targetvector.y));
            this.pos.x += this.vel.x * normalizedvector.x; //move to target
            this.pos.y += this.vel.y * normalizedvector.y + (Math.sin(this.sinvalue) * 2);

            var vectorTo = { x: this.pos.x - snowball_pos.x, y: this.pos.y - snowball_pos.y };
        };

        this.draw = function () {
            if (this.isLoaded === true && this.image.complete === true) {
                game.Entity.draw.apply(this, null); //draw using entity base
            }
        };


            /*if ((game.Entity.vectorlength(vectorTo) - this.collision_radius - snowball_col) < 0) {
                //collision has happened
                this.updatestats();
                this.vel.x = vectorTo.x * 0.3;
                this.vel.y = vectorTo.y * 0.3;

                this.state = 'struck';

                //notify snowball
                game.system.snowball.collision(vectorTo);
            }*/

        this.init();
    };