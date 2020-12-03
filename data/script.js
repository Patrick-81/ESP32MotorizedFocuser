

const cntrl = {
    avant: 0,             // déplacement entrant bouton appuyé 1 lâché 0
    arriere: 0,           // déplacement sortant bouton appuyé 1 lâché 0
    speedplus: 0,         // incrémente vitesse bouton appuyé 1 lâché 0
    speedmoins: 0,        // diminue vitesse bouton appuyé 1 lâché 0
    engaged: true,        // débraye le moteur bouton appuyé 1 lâché 0
    lockunlock: true      // débraye le moteur bouton appuyé 1 lâché 0
}

gofwd = document.getElementById("fwd");
gobwd = document.getElementById("bwd");
speedup = document.getElementById("vplus");
speeddown = document.getElementById("vmoins");
embrayer = document.getElementById("engaged");    
///////////////////////////////////////////////////////////////
// Commandes à partir de l'appareil mobile
// Mouvement avant 
gofwd.addEventListener('touchstart', function(ev) {  
    ev.preventDefault(); 
    cntrl.avant = 1;
});
gofwd.addEventListener('touchend', function(ev) {
    ev.preventDefault();
    cntrl.avant = 0;
});
// Mouvement arrière 
gobwd.addEventListener('touchstart', function(ev) {
    ev.preventDefault();
    cntrl.arriere = 1;
});
gobwd.addEventListener('touchend', function(ev) {
    ev.preventDefault();
    cntrl.arriere = 0;
});
// augmentation de la vitesse 
speedup.addEventListener('touchstart',  function(ev) {
    ev.preventDefault();
    cntrl.speedplus = 1;
});
speedup.addEventListener('touchend',  function(ev) {
});
// diminution de la vitesse 
speeddown.addEventListener('touchstart',  function(ev) {
    ev.preventDefault();
    cntrl.speedmoins = 1;

});
speeddown.addEventListener('touchend',  function(ev) {
});
// embrayage ou débrayage du moteur
embrayer.addEventListener('touchstart', function(ev) {
      ev.preventDefault();
    cntrl.lockunlock = true;
});
embrayer.addEventListener('touchend',  function(ev) {
});
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
// Commandes à partir du PC
///////////////////////////////////////////////////////////////
// augmente la vitesse
function plus() {
    cntrl.speedplus = 1;
}
// diminue la vitess
function moins() {
    cntrl.speedmoins = 1;
}
// débraye ou embraye le moteur
function debraye() {
    cntrl.lockunlock = true;
}
// mouvement avant
function startavant() {
    cntrl.avant = 1;
}
function stopavant() {
    cntrl.avant = 0;
}
// mouvement arrière
function startarriere() {
    cntrl.arriere = 1;
}
function stoparriere() {
    cntrl.arriere = 0;
}
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
// boucle d'actuation
//////////////////// boucle d'actuation ///////////////////////
function loop() {
     if (cntrl.avant == 1)
    {
        var xhttp = new XMLHttpRequest();
        xhttp.open("GET", "avant", true);
        xhttp.send();
    } 
    else if(cntrl.arriere == 1)
    {
        var xhttp = new XMLHttpRequest();
        xhttp.open("GET", "arriere", true);
        xhttp.send();
    } 
    else if (cntrl.speedplus == 1 )
    {
        var xhttp = new XMLHttpRequest();
        xhttp.open("GET", "vplus", true);
        xhttp.send(); 
        cntrl.speedplus = 0;
    } 
    else if (cntrl.speedmoins == 1 )
    {
        var xhttp = new XMLHttpRequest();
        xhttp.open("GET", "vmoins", true);
        xhttp.send();        
        cntrl.speedmoins = 0;
    }
    else if (cntrl.lockunlock)
    {
        cntrl.engaged = !cntrl.engaged;
        if (cntrl.engaged)
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
        cntrl.lockunlock = false;
     }
}
loopon = setInterval(loop, 100);
///////////////////// fin d'actuation /////////////////////////

///////////////////////////////////////////////////////////////
// boucle d'actualisation de l'affichage
////////////// actualisation de l'affichage ///////////////////

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
}
// mets à jour les champs de la page html
getdata = setInterval(getData, 300);
////////////// fin actualisation de l'affichage ////////////////
