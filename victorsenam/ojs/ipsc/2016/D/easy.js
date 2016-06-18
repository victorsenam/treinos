var log = "";
var curCommand = 0;
var active = true;

var elements = [
['red square', 80, 80],
['green square', 80, 180],
['blue square', 80, 280],
['yellow square', 180, 80],
['orange square', 180, 180],
['pink square', 180, 280],
['red wide', 280, 80],
['green wide', 280, 180],
['blue wide', 280, 280],
['yellow wide', 480, 80],
['orange wide', 480, 180],
['pink wide', 480, 280]
];

function process(e) {
  if (active) {
    var x = e.pageX - e.target.offsetLeft;
    var y = e.pageY - e.target.offsetTop;
    log = log + x + " " + y + "\n";
    displayLog();
  }
}

function getPos(cm, el) {
  return cm.search(elements[el][0]);
}

function next() {
  if (active) {
    if (curCommand == commands.length) {
      log = log + "done\n";
      document.getElementById("command").innerHTML = "Congratulations. Submit your action log.";
      active = false;
      displayLog();
    } else {
      log = log + "next\n";
      document.getElementById("command").innerHTML = "<b>Level " + (curCommand+2) + ":</b> " + commands[curCommand] + " Then click on the <b>Next</b> button.";

      var i;
      var action = "";
      var maxi = 0;
      var cmd = commands[curCommand];
      var val = -1;
      do {
        maxi = 0;
        val = -1;
        for (i = 0; i < elements.length; i++) {
          if (getPos(cmd, i) > getPos(cmd, maxi))
            maxi = i;
        }
        val = getPos(cmd, maxi);
        if (val != -1) {
          action = elements[maxi][1] + " " + elements[maxi][2] + "\n" + action;
          cmd = cmd.substring(0, val);
        }
      } while (val != -1);

      if (action == "")
        console.log("fodeu");
      log = log + action;

      displayLog();

      curCommand += 1;
      next();
    }
  }
}

function displayLog() {
  document.getElementById('log').value = log;
}
