// This script adjusts the Wavegen offset based on Scope measurement.
clear(); // clear log
if(!('Wavegen' in this) || !('Scope' in this)) throw "Please open a Scope and a Wavegen instrument"; // open scope & wave


//// CHANGE THESE VALUES!!!!!  ################
var high = 5;
var low = 0;
var fs = 4000;
var sec = 60;

var TimeLed = 3; //Sec
var incrementLed = 0;
var MaxClasses = 3; // index modolo(MaxClasses) = {0 = resting, 1 = upp, 2 = Statick hold, 3 = down}
//#######################################

// setting all variables for script
var time = new Date();
var date = time.getUTCFullYear()+"_"+time.getUTCMonth()+"_"+time.getUTCDate();
print(date); 
var TestSubjectID =   Tool.getText("TestSubject ID","ID");
var TestSubjectARM =   Tool.getText("Which arm ","R=Right or L= Left");
var DataPath = "C:/Users/Elliot/Desktop/åk3/EXO2/Data/DataIndex.txt";
var index = File(DataPath).read(3);
var path = "C:/Users/Elliot/Desktop/åk3/EXO2/Data/"+date+"_TestSub"+TestSubjectID+"_"+"ARM_"+TestSubjectARM+"_"+index+".csv";
var file = File(path);
var text = "TID(SEC);AMP(V) Channel 1;AMP(V) Channel 2;CLASS\n";
var remaining = 0;
var lable = 0;


// opening and setting everything for Wavegen
Wavegen.run();
Wavegen.Channel1.Simple.Type.value = "DC";
Wavegen.Channel1.Mode.text = "Simple";
Wavegen.Channel1.Simple.Offset.value = 0;

Wavegen.Channel2.Simple.Type.value = "DC";
Wavegen.Channel2.Mode.text = "Simple";
Wavegen.Channel2.Simple.Offset.value = 0;


// opening and setting everything for Scope1
Scope.run();
Scope.Trigger.text = "Repeated";
Scope1.Time.Position.value = 0;
Scope1.Time.Rate.value = fs;
Scope1.Time.Samples.value= fs*sec;//number of samples
Scope1.Time.Mode.text= "Record";//record setting of the scope so that the values can be saved


 Wavegen.Channel1.Simple.Offset.value = low;
 Wavegen.Channel2.Simple.Offset.value = low;

// if(!wait(1)) throw "Canceled" // for time to config 

for(var i = 0; i < round(sec/TimeLed); i++){

 
      remaining = i%MaxClasses;
      if(remaining == 1)
      {
        lable = 1;
             Wavegen.Channel1.Simple.Offset.value = high;
             Wavegen.Channel2.Simple.Offset.value = low;
      }
      else if(remaining == 2)
      {
        lable = 2;
             Wavegen.Channel1.Simple.Offset.value = low;
             Wavegen.Channel2.Simple.Offset.value = high;
      }
      else if(remaining == 3)
      {
        lable = 3;
             Wavegen.Channel1.Simple.Offset.value = high;
             Wavegen.Channel2.Simple.Offset.value = high;
      }
      else
      {
        lable = 0;
             Wavegen.Channel1.Simple.Offset.value = low;
             Wavegen.Channel2.Simple.Offset.value = low;
      }
    if(!wait(TimeLed)) throw "Canceled"
}

var d1 = Scope.Channel1.data;
var d2 = Scope.Channel2.data;

const d = [d1,d2];

//---------------printing and saving data
var t = 1/fs;
var i = 1;
d1.forEach(function(sample)
{
    i++
    t = i/fs;

  if(i % (TimeLed*fs)  == 0)
    {
      
      incrementLed ++;
      remaining = incrementLed%MaxClasses;
      if(remaining == 1)
      {
        lable = 1;
      }
      else if(remaining == 2)
      {
        lable = 2;
      }
      else if(remaining == 3)
      {
        lable = 3;
      }
      else
      {
        lable = 0;
      }
    print(lable);
    }

    text = text + t+";"+ d2[i] +";" + sample+";" + lable+"\n";
})
 
File(path).writeLine(text);
//incrementing for next file 
index ++;
File(DataPath).writeLine(index);
Scope.stop();
Wavegen.stop();
