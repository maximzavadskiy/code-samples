// For an introduction to the Blank template, see the following documentation:
// http://go.microsoft.com/fwlink/?LinkId=232509
(function () {
    "use strict";

    WinJS.Binding.optimizeBindingReferences = true;

    var app = WinJS.Application;
    var activation = Windows.ApplicationModel.Activation;
    
   WinJS.strictProcessing();
   var canvas, context,stage;
    var bgImage, p1Image, p2Image, ammoImage, p1Lives, p2Lives, title, endGameImage;
    var bgBitmap, p1Bitmap, ammoBitmap;
    var preload;
    var bmp_grass, bmp,img,img_grass;

    //calculate display scale factor - Original game assets assume 800x400
    var SCALE_X = window.innerwidth / 800;
    var SCALE_Y = window.innerHeight / 400;
    var MARGIN = 25; //inset from edge of screen
    var GROUND_Y = 390 * SCALE_Y, im;
     

    app.onactivated = function (args) {
        if (args.detail.kind === activation.ActivationKind.launch) {
            if (args.detail.previousExecutionState !== activation.ApplicationExecutionState.terminated) {
                // TODO: This application   1 has been newly launched. Initialize
                // your application here.
 

            } else {
                // TODO: This application has been reactivated from suspension.
                // Restore application state here.
            }
            args.setPromise(WinJS.UI.processAll());
        }
    };


    function initialize() {
     
        canvas = document.getElementById("gameCanvas");
        stage = new createjs.Stage(canvas);
        stage.autoClear = true;
        img = new Image();
        img.src = "images/HUD/Bee.png";
        img.style.height = 10;
        img.style.width = 50;

        img_grass = new Image();
        img_grass.src = "images/HUD/grass.jpg";
        bmp = new createjs.Bitmap(img);
        bmp.scaleX = bmp.scaleY = 2;

        bmp_grass = new createjs.Bitmap(img_grass);

        bmp_grass.scaleX = bmp.scaleY = 2;

        stage.addChild(bmp);

        bmp_grass.x = 0;
        bmp_grass.y = gameCanvas.height - 700;
        stage.addChild(bmp_grass);

        stage.update();

        createjs.Ticker.addListener(window);
        createjs.Ticker.setFPS(30)
    }


    function prepareGame()
    {
        //bgImage = preload.getResult("screenImage");
        //bmp_grass.x = bmp_grass.x + 50;
        //if (bmp_grass.x > bmp_grass.canvas.width) { bmp_grass.x = 0; }

        angle += 0.83;
        //bmp.y =  (Math.sin(-angle)*10  );
        bmp.x = stage.mouseX * 1;

        bmp.y = stage.mouseY + (Math.sin(-angle) * 10);
        stage.update(); 
    }

    function gameLoop()
    {
        update();
        draw();
    }

    function update() { }

    function draw() { }

    app.oncheckpoint = function (args) {
        // TODO: This application is about to be suspended. Save any state
        // that needs to persist across suspensions here. You might use the
        // WinJS.Application.sessionState object, which is automatically
        // saved and restored across suspension. If you need to complete an
        // asynchronous operation before your application is suspended, call
        // args.setPromise().
    };

    document.addEventListener("DOMContentLoaded", initialize, false);
    app.start();
})();
