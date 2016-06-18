var elements = {
  'anywhere': {
    pos: [10, 10]
  },
  'background': {
    pos: [10, 10]
  },
  'square': {
    options: [
      [80, 80],
      [80, 180],
      [80, 280],
      [180, 80],
      [180, 180],
      [180, 280]
    ]
  },
  'wide': {
    options: [
      [280, 80],
      [280, 180],
      [280, 280],
      [480, 80],
      [480, 180],
      [480, 280]
    ]
  }
};
var colors = {
  'yellow': [255, 255, 0, 255],
  'pink': [255, 0, 255, 255],
  'green': [0, 255, 0, 255],
  'red': [255, 0, 0, 255],
  'blue': [0, 0, 255, 255],
  'orange': [255, 136, 0, 255]
}
var res = "";

function getPos (cmd, act) {
  var keys = Object.keys(act);
  
  if (keys.includes('pos')) {
    return act.pos;
  } else if (keys.includes('options')) {
    var color;
    var ckeys = Object.keys(colors);
    for (var i = 0; i < ckeys.length; i++)
      if (cmd.search(ckeys[i]) != -1)
        color = ckeys[i];
    var opt = act.options;
    var ctx = document.getElementById("canimg").getContext('2d');
    for (var i = 0; i < opt.length; i++) {
      if (ctx.getImageData(opt[i][0], opt[i][1], 1, 1).data.toString() == colors[color].toString()) {
        return opt[i];
      }
    }
  }

  for (var i = 0; i < keys.length; i++)
    if (cmd.search(keys[i]) != -1) {
      return getPos(cmd, act[keys[i]]);
    }
  return [-1, -1];
}

function actionEnd () {
  return " " + (Date.now()+timeshift)/1000 + "\n";
}

function obeyCommand (cmds) {
  if (cmds.length > 0) {
    var cmd = cmds.pop();
    
    if (cmd.search(/next/i) != -1) {
      res = res + "next" + actionEnd();
      next();
      obeyCommand(cmds);
    } else if (cmd.search(/congrat/i) != -1) {
      console.log("fim!");
    } else if (cmd.search("seconds") != -1) {
      var secs = parseInt(cmd.match(/\d*(?= seconds)/g)[0]);
      //console.log("esperando " + secs + "s");
      timeshift += secs*1000;
      obeyCommand(cmds);
    } else { 
      var times = 1;
      if (cmd.search("times") != -1)
        times = parseInt(cmd.match(/\d*(?= times)/g)[0]);

      var pos = getPos(cmd, elements);

      if (pos[0] == -1)
        console.log("ERRO : Não sei fazer " + cmd);
      
      for (var i = 0; i < times; i++)
        res = res + pos[0] + " " + pos[1] + actionEnd();
      obeyCommand(cmds);
    }
  } else {
    setTimeout(go, 10);
  }
  document.getElementById("log").value = res;
}

function go () {
    var cmdstring = document.getElementById("command").innerHTML;
    var commands = cmdstring.split(/then/i).reverse();

    obeyCommand(commands);
}
