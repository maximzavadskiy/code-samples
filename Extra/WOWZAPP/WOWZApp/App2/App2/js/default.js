// For an introduction to the Blank template, see the following documentation:
// http://go.microsoft.com/fwlink/?LinkId=232509
var gameCtx;

//(function () {
    "use strict";
    
    WinJS.Binding.optimizeBindingReferences = true;

    var app = WinJS.Application;
    var activation = Windows.ApplicationModel.Activation;
    
   WinJS.strictProcessing();
    var canvas, context, stage;
    var bgImage, p1Image, p2Image, ammoImage, p1Lives, p2Lives, title, endGameImage;
    var bgBitmap, p1Bitmap, ammoBitmap;
    var preload;
    var bmp_grass, bmp, img, img_grass;

    var obstacles = new Array();
    var obstacle_sprite1, obstacle_sprite2, obstacle_sprite3, obstacle_sprite4, obstacle_sprite5, obstacle_sprite6, obstacle_sprite7, obstacle_sprite8, obstacle_sprite9, obstacle_sprite10, obstacle_sprite11, obstacle_sprite12, obstacle_sprite13;
    var victory_sprite;

    var obstacle_sprite;
    var mainCharacter;

    var n = 500;
    var dragok = false;
    var y, x, d, dy, dx;
    var e;
    var blowFlag = true;
    var flagLevelCompleted = false;

    var blowAvailable = true;

    //calculate display scale factor - Original game assets assume 800x400
    var screenWidth = 1377;
    var screenHeight = 768;

    var SCALE_X = window.innerwidth / screenWidth;
    var SCALE_Y = window.innerHeight / screenHeight;
    var MARGIN = 25; //inset from edge of screen
    var GROUND_Y = innerHeight*0.8 * SCALE_Y;
     
    var sampleObstacle;

    app.onactivated = function (args) {
        if (args.detail.kind === activation.ActivationKind.launch) {
            if (args.detail.previousExecutionState !== activation.ApplicationExecutionState.terminated) {
                // TODO: This application   1 has been newly launched. Initialize
                // your application here.
                //GameManager.game.initialize(GameManager.state 
                WinJS.UI.processAll()
                WinJS.Navigation.navigate("/html/homePage.html");
 

            } else {
                // TODO: This application has been reactivated from suspension.
                // Restore application state here.
            }
            args.setPromise(WinJS.UI.processAll());
           
        }
    };


        var _assetsToLoad = 0;

        var addImage = function (src) {
            var img = new Image();
            img.src = src;
            _assetsToLoad++
        img.addEventListener('load', function ()
        {
                _assetsToLoad--;
            }, false);
            return img;
        }

    function initialize() {



        timer = new Timer();

        var addMainImage = function (src) {
            var img = new Image();
            img.src = src;
            img.className = "dragClass";

            
            return img;
        }

        mainCharacter = { x:0 , y:0, image: null};
        mainCharacter.image = addMainImage("images/fireguy.png");


        var checkResources = function () {
            if (_assetsToLoad == 0)
                draw();
            else
                setTimeout(checkResources, 200);
        }

        loadObstacleSprites();
       // obstacle_sprite1 = addImage("images/obstacles/cloud001.png");
       // obstacle_sprite2 = addImage("images/obstacles/cloud002.png");
       // obstacle_sprite3 = addImage("images/obstacles/cloud003.png");
       // obstacle_sprite4 = addImage("images/obstacles/cloud004.png");
       // obstacle_sprite5 = addImage("images/obstacles/cloud005.png");

        //obstacle_sprite = addImage("images/bluebox.png");

        checkResources();


        var move = function(e) {
            if (!e) e = window.event;
            if (dragok) {
                d.style.left = (e.clientX > 0) ? (dx + e.clientX - x + "px") : (0 + "px");
                d.style.top = (e.clientY > 0) ? (dy + e.clientY - y + "px") : (0 + "px");
                return false;
            }
        }

        var down = function (e) {

            if ((e.clientX < mainCharacter.x + mainCharacter.image.width) && (e.clientX > mainCharacter.x)
               && (e.clientY < mainCharacter.y + mainCharacter.image.height) && (e.clientY > mainCharacter.y)) {

                dragok = true;
                mainCharacter.image.style.zIndex = n++;

                return false;
                
            }
        }



        function blower(x,y)
        {
            var x, y;




                }

        var hold = function (e)
        {
            if (dragok) {
                mainCharacter.x = (e.clientX > mainCharacter.image.height / 2) ? e.clientX - (mainCharacter.image.height / 2) : 0;
                mainCharacter.y = (e.clientY > mainCharacter.image.width / 2) ? e.clientY - (mainCharacter.image.width / 2) : 0;
            }
        }

        var up = function () {
            dragok = false;
            document.onmousemove = null;
        }

        var exitBlow = false;
        var blow = function ()
        {
            //if (exitBlow) return;
            if (!blowAvailable) return;

            if (blowFlag)
            {
                mainCharacter.image = addMainImage("images/fireguyfiring.png");
                exitBlow = true;
                setInterval(
                    function ()
                    {
                        blowAvailable = false;
                        exitBlow = false
                        blowFlag = true;
                        
                        mainCharacter.image = addMainImage("images/fireguy.png");

                        setInterval(function () { this.blowAvailable = true; console.log("availbale"); }, 2000);

                    }, 1000);

                blowFlag = false;
            }
            else
            {
                mainCharacter.image = addMainImage("images/fireguy.png");
                blowFlag = true;
            }

        }



        canvas = document.getElementById("gameCanvas");
        canvas.width = window.innerHeight * 2;
        canvas.height = window.innerWidth * 2;
        context = canvas.getContext("2d");

        canvas.addEventListener('MSPointerUp', function () { up(); }, false);
        canvas.addEventListener('MSPointerDown', function (e) { down(e); }, false);
        canvas.addEventListener('MSPointerMove', function (e) { hold(e); }, false);
        canvas.addEventListener('dblclick', function () { blow(); }, false);
        

        preload = new createjs.PreloadJS();
        preload.onComplete = checkResources;

        addObstacles();
        resetMainCharacter();

        var manifest = [
            { id: "bee", src: "images/fireguy.png" },
             { id: "screenImage", src: "images/Backgrounds/gameplay_screen.png" },

        ];
        preload.loadManifest(manifest);

    }


    /*function prepareGame()
    {
        //bgImage = preload.getResult("screenImage").result;
        //bgBitmap = new createjs.Bitmap(bgImage);
        //bgBitmap.scaleX = SCALE_X;
        //bgBitmap.scaley = SCALE_Y;


        draw();
        //stage.draw();
    }*/

    function draw()
    {
        clearCanvas();// clear canvas from previous frame
        drawBackgroud();

        checkLevelFinished();

 
        drawObstacles();
        drawMainCharacter();
        checkCharacterCollision();
        checkObstacleToBlow();


        requestAnimationFrame(draw);

    }
    
    function checkLevelFinished()
    {
        if (flagLevelCompleted)
        {
            context.drawImage(victory_sprite, screenWidth / 2 - victory_sprite.width / 2, screenHeight / 2);
            mainCharacter.image = addImage("images/fireguy.png");
            mainCharacter.x = screenWidth / 2;
            mainCharacter.y = screenHeight;

            blowFlag = false;
        }
    }

    function checkObstacleToBlow()
    {
        if (blowFlag) return;
        for (var i = 0; i < obstacles.length; i++)
        {
            var obs = obstacles[i];
            var ch = { x: mainCharacter.x + mainCharacter.image.width, y: mainCharacter.y, width: 80, height: 300 };

            if (hasCollision(obs.x, obs.y, obs.sprite.height, obs.sprite.height, ch.x, ch.y, ch.width, ch.height))
            {
                if (obs.sprite === obstacle_boss)
                {
                    flagLevelCompleted = true;
                }

                obstacles[i] = null;
                for (var j = i + 1; j < obstacles.length; j++) obstacles[j - 1] = obstacles[j];
                obstacles.pop();

                //addMoreObstacles();
            }

        }
    }

    function checkCharacterCollision()
    {
        for (var i = 0; i < obstacles.length; i++)
        {
            var obs = obstacles[i];
            var ch = mainCharacter;
            //console.log("x:"+obs.x+ "y:"+obs.y +" "+obs.width+ " " +obs.height) ;
            //console.log("dimensions" + obs.sprite.height + " " + obs.sprite.width);
            if (hasCollision(obs.x, obs.y, obs.sprite.height, obs.sprite.height, ch.x, ch.y, ch.image.width, ch.image.height))
            {
                resetMainCharacter();
                obstacles[i] = null;
                for (var j = i + 1; j < obstacles.length; j++) obstacles[j-1] = obstacles[j];
                obstacles.pop();
                addMoreObstacles();
            }

        }
    }

    function resetMainCharacter()
    {
        mainCharacter.x = 0;
        mainCharacter.y = screenHeight/2;
        dragok = false;
    }

    var collisionLimit=0;//in pixels, how many pixels deep to be collision
    var collisionScale = 0.6;

    function hasCollision(x1,y1,w1,h1,  x2,y2,w2,h2) //returns bool, top left corner coords and dimensions
    {
        x1=x1+w1/2;  y1=y1+h1/2;
        x2=x2+w2/2;  y2=y2+h2/2;

        return ( (Math.abs(x1 - x2) <= (w1*collisionScale/2 + w2*collisionScale/2 + collisionLimit) && (Math.abs(y1 - y2) <= h1*collisionScale/2 + h2*collisionScale/2 + collisionLimit) ));
    }

    function drawMainCharacter()
    {
        context.drawImage(mainCharacter.image, mainCharacter.x, mainCharacter.y);
    }

    function clearCanvas()
    {
        context.clearRect(0, 0, canvas.width, canvas.height);
    }

    function loadObstacleSprites()
    {
        obstacle_sprite1 = addImage("images/obstacles/cloud001.png");//600
        obstacle_sprite2 = addImage("images/obstacles/cloud002.png");//1000
        obstacle_sprite3 = addImage("images/obstacles/cloud003.png");//400
        obstacle_sprite4 = addImage("images/obstacles/cloud004.png");//900 500
        obstacle_sprite5 = addImage("images/obstacles/cloud005.png");//400 267
        obstacle_sprite6 = addImage("images/obstacles/cloud006.png");//300
        obstacle_sprite7 = addImage("images/obstacles/cloud007.png");//700 373
        obstacle_sprite8 = addImage("images/obstacles/cloud008.png");//500
        obstacle_sprite9 = addImage("images/obstacles/cloud009.png");//400 288
        obstacle_sprite10 = addImage("images/obstacles/cloud010.png");//900
        obstacle_sprite11 = addImage("images/obstacles/cloud011.png");//1000
        obstacle_sprite12 = addImage("images/obstacles/cloud012.png");//400
        obstacle_sprite13 = addImage("images/obstacles/cloud013.png");//200

        obstacle_boss = addImage("images/obstacles/nemesis.png");//200

        background = addImage("images/Backgrounds/gamebg.png");//200

        victory_sprite = addImage("images/Backgrounds/congrats.png");
    }

    function addObstacles()
    {
        var sw = screenWidth;
        addObstacle({ appearTime: 1, x: sw, y: 150, velocityx: 4, velocityy: 0.5, sprite: obstacle_sprite6 });
        addObstacle({ appearTime: 2, x: sw, y: 150, velocityx: 3, velocityy: 0.1, sprite: obstacle_sprite13 });
        addObstacle({ appearTime: 3, x: sw, y: 250, velocityx: 4, velocityy: -0.5, sprite: obstacle_sprite3 });
        addObstacle({ appearTime: 4, x: sw, y: 300, velocityx: 7, velocityy: -0.3, sprite: obstacle_sprite4 });
        addObstacle({ appearTime: 5, x: sw, y: 450, velocityx: 6, velocityy: -0.4, sprite: obstacle_sprite12 });
        addObstacle({ appearTime: 6, x: sw, y: 450, velocityx: 6, velocityy: -0.4, sprite: obstacle_sprite6 });
        addObstacle({ appearTime: 7, x: sw, y: 450, velocityx: 6, velocityy: -0.4, sprite: obstacle_sprite7 });
        addObstacle({ appearTime: 8, x: sw, y: 450, velocityx: 6, velocityy: -0.4, sprite: obstacle_sprite8 });
        addObstacle({ appearTime: 9, x: sw, y: 450, velocityx: 6, velocityy: -0.4, sprite: obstacle_sprite9 });
        addObstacle({ appearTime: 10, x: sw, y: 450, velocityx: 6, velocityy: -0.4, sprite: obstacle_sprite10 });

        addObstacle({ appearTime: 12, x: sw, y: screenHeight / 2 - obstacle_boss.height, velocityx: 3, velocityy: 0.5, sprite: obstacle_boss });

        addObstacle({ appearTime: 12, x: sw, y: screenHeight / 2, velocityx: 10, velocityy: -0.4, sprite: obstacle_sprite13 });
        addObstacle({ appearTime: 12.3, x: sw, y: screenHeight / 2, velocityx: 10, velocityy: 0.4, sprite: obstacle_sprite13 });
        addObstacle({ appearTime: 12.6, x: sw, y: screenHeight / 2, velocityx: 10, velocityy: 0, sprite: obstacle_sprite13 });
        addObstacle({ appearTime: 12.9, x: sw, y: screenHeight / 2, velocityx: 10, velocityy: 1, sprite: obstacle_sprite13 });
        addObstacle({ appearTime: 13.1, x: sw, y: screenHeight / 2, velocityx: 10, velocityy: -1, sprite: obstacle_sprite13 });

    }

    function addMoreObstacles()
    {
        /*addObstacle({ x: 1000, y: 150, velocityx: 1, velocityy: -0.1, sprite: obstacle_sprite1 });
        addObstacle({ x: 1000, y: 150, velocityx: 1, velocityy: -0.45, sprite: obstacle_sprite2 });
        addObstacle({ x: 1500, y: 150, velocityx: 8, velocityy: -1, sprite: obstacle_sprite3 });
        addObstacle({ x: 1500, y: 450, velocityx: 4, velocityy: 1.5, sprite: obstacle_sprite4 });
        addObstacle({ x: 1500, y: 50, velocityx: 3, velocityy: 1, sprite: obstacle_sprite5 });
        */
    }

    function addObstacle(o)
    {
        obstacles.push({ appearTime: o.appearTime, x: o.x, y: o.y, width: o.sprite.width, height: o.sprite.height, velocityx: o.velocityx, velocityy: o.velocityy, sprite: o.sprite });
    }

    function drawBackgroud()
    {
        context.drawImage(background, 0, 0);
    }

    function drawObstacles() {
        for (var i = 0; i < obstacles.length; i++) {
            if(obstacles[i].appearTime>timer.getTimeSeconds()) continue;

           // console.log(" obs:"+obstacles[i].appearTime);

            var sprite = obstacles[i].sprite;
            context.drawImage(sprite, obstacles[i].x, obstacles[i].y);
            //comment
            obstacles[i].x -= obstacles[i].velocityx/2;
            obstacles[i].y -= obstacles[i].velocityy/2;
        }
    }


    function show() {
        var i = 0;
        var a = 0;
        var l = document.getElementsByTagName('a');
        if (i < l.length - 1) {
            l[i].style.display = "none";
            i++;
        } else {
            for (a = 0; a < l.length - 1; a++) {
                l[a].style.display = "block";
                i = 0;
            }
        }
    }
    setInterval(show, 1000);
    app.oncheckpoint = function (args) {
        // TODO: This application is about to be suspended. Save any sftate
        // that needs to persist across suspensions here. You might use the
        // WinJS.Application.sessionState object, which is automatically
        // saved and restored across suspension. If you need to complete an
        // asynchronous operation before your application is suspended, call
        // args.setPromise().
    };

    document.addEventListener("DOMContentLoaded", initialize, false);
    app.start();


    Timer = function ()
    {
        var d = new Date();
        startTime = d.getTime();

        this.getTimeSeconds = function ()
        {
            var d = new Date();
            return (d.getTime() - startTime) / 1000;
        }
    }