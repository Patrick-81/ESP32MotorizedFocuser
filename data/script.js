


var switchavant = 0; // déplacement entrant bouton appuyé 1 lâché 0
var switcharriere = 0;// déplacement sortant bouton appuyé 1 lâché 0
var switchspeedplus = 0;// incrémente vitesse bouton appuyé 1 lâché 0
var switchspeedmoins = 0;// diminue vitesse bouton appuyé 1 lâché 0
var engaged = true;// débraye le moteur bouton appuyé 1 lâché 0
var lockunlock = true;// débraye le moteur bouton appuyé 1 lâché 0
document.addEventListener('DOMContentLoaded', (event) => {
    gofwd = document.getElementById("fwd");
    gobwd = document.getElementById("bwd");
    speedup = document.getElementById("vplus");
    speeddown = document.getElementById("vmoins");
    embrayer = document.getElementById("engaged");    
    //the event occurred
})


gofwd.addEventListener('touchstart', function(ev) {  
    ev.preventDefault(); 
    switchavant =1;
});
gofwd.addEventListener('touchend', function(ev) {
    ev.preventDefault();
    switchavant = 0;
});

gobwd.addEventListener('touchstart', function(ev) {
    ev.preventDefault();
    switcharriere =1;
});
gobwd.addEventListener('touchstart', function(ev) {
    ev.preventDefault();
    switcharriere = 0;
});

speedup.addEventListener('touchstart',  function(ev) {
    ev.preventDefault();
    switchspeedplus = 1;
});
speedup.addEventListener('touchend',  function(ev) {
});


speeddown.addEventListener('touchstart',  function(ev) {
    ev.preventDefault();
    switchspeedmoins = 1;
});
speeddown.addEventListener('touchend',  function(ev) {
});

embrayer.addEventListener('touchstart', function(ev) {
      ev.preventDefault();
      lockunlock = true;
});
embrayer.addEventListener('touchend',  function(ev) {
});

// réglage de =1 la vitesse
function plus() {
    switchspeedplus = 1;
}

function moins() {
    switchspeedmoins = 1;
}

// débraye le moteur
function debraye() {
    lockunlock  = true;
}
function startavant() {
    // console.log(ev.touches);
    switchavant = 1;
    // if(loopon == 0) loop();
}

function stopavant() {
    // console.log(ev.touches);
    switchavant = 0;
    // if(loopon == 0) loop();
}

function startarriere() {
    switcharriere = 1;
    // if(loopon == 0) loop();
}

function stoparriere() {
    switcharriere = 0;
    // if(loopon == 0) loop();
}


function loop() {
     if (switchavant == 1)
    {
        var xhttp = new XMLHttpRequest();
        xhttp.open("GET", "avant", true);
        xhttp.send();
    } 
    else if(switcharriere == 1)
    {
        var xhttp = new XMLHttpRequest();
        xhttp.open("GET", "arriere", true);
        xhttp.send();
    } 
    else if (switchspeedplus == 1 )
    {
        var xhttp = new XMLHttpRequest();
        xhttp.open("GET", "vplus", true);
        xhttp.send(); 
        switchspeedplus = 0;
    } 
    else if (switchspeedmoins == 1 )
    {
        var xhttp = new XMLHttpRequest();
        xhttp.open("GET", "vmoins", true);
        xhttp.send();        
        switchspeedmoins = 0;
    }
    else if (lockunlock)
    {
        engaged = !engaged;
        if (engaged)
        {
            document.getElementById('engaged').innerText = "DEBRAYE";
            document.getElementById("engaged").style.background='#FF5733'
        }
        else
        {
            document.getElementById('engaged').innerText = "EMBRAYE";
            document.getElementById("engaged").style.background='#DAF7A6'
        }
        var xhttp = new XMLHttpRequest();
        xhttp.open("GET", "lock", true);
        xhttp.send();
        lockunlock = false;
     }
    // t=setTimeout('loop()',200);
}

loopon = setInterval(loop, 100);

// document.getElementById("bwd").addEventListener("onmouseup", function(){ switchavant = 1;});
// document.getElementById("fwd").addEventListener("onmousedown", function(){ switchavant = 0;});
// document.getElementById("bwd").addEventListener("onmouseup", stopavant);
// document.getElementById("bwd").addEventListener("onmousedown", startavant);
// document.getElementById("fwd").addEventListener("onmouseup", stoparriere);
// document.getElementById("fwd").addEventListener("onmousedown", startarriere);




function getData()
{
    var pos = new XMLHttpRequest();
    var speed = new XMLHttpRequest();
    var eng = new XMLHttpRequest();

    pos.onreadystatechange = function()
    {
        if(this.readyState == 4 && this.status == 200)
        {
            document.getElementById("position").innerHTML = this.responseText;
        }
    };
    pos.open("GET", "position", true);
    pos.send();

    speed.onreadystatechange = function()
    {
        if(this.readyState == 4 && this.status == 200)
        {
            document.getElementById("speed").innerHTML = this.responseText;
        }
    }; 
    speed.open("GET", "speed", true);
    speed.send();

    // eng.onreadystatechange = function()
    // {
    //     if(this.readyState == 4 && this.status == 200)
    //     {
    //         let lbl = document.getElementById('engaged');
    //         if (strcmp(lbl.innerText, this.responseText) === -1 )
    //         {
    //             lbl.innerText = this.responseText;
    //             document.getElementById("button").style.background='#000000'
    //         }
    //         else
    //         {

    //         }
    //     }
    // }; 
    // eng.open("GET", "engaged", true);
    // eng.send();
   
}
// mets à jour les champs de la page html
getdata = setInterval(getData, 300);