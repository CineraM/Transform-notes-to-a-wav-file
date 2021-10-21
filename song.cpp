#include "wavfilewriter.h"
#include "song.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

Note::Note(string str){//implementing the constructor
    int oct;
    if(str[1] < 'A' && str[1] != '#'){ 
        switch(str[0]){
          case 'R':
            pitch = REST;
            break;
          case 'A':
            pitch = A;
            break;
          case 'B':
            pitch = B;
            break;
          case 'C':
            pitch = C;
            break;
          case 'D':
            pitch = D;
            break;
          case 'E':
            pitch = E;
            break;
          case 'F':
            pitch = F;
            break;
          case 'G':
            pitch = G;
            break;
        }
        stringstream to_int;
        to_int << str[1];
        to_int >> oct;
        octave = oct;

        if(str[3] == '.'){
          switch(str[2]){
            case 'q':
              duration = 1.0*1.5;
              break;
            case 'h':
              duration = 2.0*1.5;
              break;
            case 'w':
              duration = 4.0*1.5;
              break;
            case 'e':
              duration = 0.5*1.5;
              break;
            case 's':
              duration = 0.25*1.5;
              break;
          }
        }else{
          switch(str[2]){
            case 'q':
              duration = 1.0;
              break;
            case 'h':
              duration = 2.0;
              break;
            case 'w':
              duration = 4.0;
              break;
            case 'e':
              duration = 0.5;
              break;
            case 's':
              duration = 0.25;
              break;
          }
        }
      } else {
        string pch = "";
        pch += str[0];
        pch += str[1];

        if(pch.compare("Db") == 0){
          pitch = Db;
        }else if(pch.compare("Eb") == 0){
          pitch = Eb;
        }else if(pch.compare("Gb") == 0){
          pitch = Gb;
        }else if(pch.compare("Ab") == 0){
          pitch = Ab;
        }else if(pch.compare("Bb") == 0){
          pitch = Bb;
        }else if(pch.compare("A#") == 0){
          pitch = Bb;
        }else if(pch.compare("C#") == 0){
          pitch = Db;
        }else if(pch.compare("D#") == 0){
          pitch = Eb;
        }else if(pch.compare("F#") == 0){
          pitch = Gb;
        }else if(pch.compare("G#") == 0){
          pitch = Ab;
        }
        stringstream to_int;
        to_int << str[2];
        to_int >> oct;
        octave = oct;
        if(str[4] == '.'){
          switch(str[3]){
            case 'q':
              duration = 1.0*1.5;
              break;
            case 'h':
              duration = 2.0*1.5;
              break;
            case 'w':
              duration = 4.0*1.5;
              break;
            case 'e':
              duration = 0.5*1.5;
              break;
            case 's':
              duration = 0.25*1.5;
              break;
          }
        }else{
          switch(str[3]){
            case 'q':
              duration = 1.0;
              break;
            case 'h':
              duration = 2.0;
              break;
            case 'w':
              duration = 4.0;
              break;
            case 'e':
              duration = 0.5;
              break;
            case 's':
              duration = 0.25;
              break;
          }
        }
    }
}
Voice::Voice(const string& str, double vol, instrument_t instr){
  Note note(str);//just create a note obj inside the onstructor
}                //no need for any extra logic here
Song::Song(const string& file){
// storing all lines from the file in a string vector
    vector<string> lines;
// variables for storing the strings
    string a, b, hold;
    int count = 0;
    bool flag = true;
    
    ifstream in(file);
    ostringstream oss;

    while(getline(in, a)){
    if(flag){
      stringstream ss(a);
      ss >> tempo;//assigning the tempo aka the 1st line
      flag = false;
    }else{
      istringstream cc(a);
      if(cc >> b){      //storing the rest of the lines on the
        hold = cc.str();//string vector
        lines.push_back(hold);
        count++;//counting how many lines of notes there are
      }
    }
  }
  in.close();
  vector<Note> notes;
  for(int i = 0; i<count; i++){
    hold = "";
    //const double DEFAULT_VOLUME = 1000.0;
    //const instrument_t DEFAULT_INSTRUMENT = ORGAN;
    //^^^^^ are the default values
    Voice voice(lines[i], 1000.0, ORGAN);

    istringstream read(lines[i]);
    while(read >> hold){
      Note note(hold);            //passes to the note constructor 
      voice.addNote(note);        //then adds the note to 
      voice.setInstrument(ORGAN); //the notes vec from the note class
      voice.setVolume(1000.0);    //setvol/ints are setting the 
    }                             //note's insr and vol
    voices.push_back(voice);
    voice.clear();
  }
}

ostream& operator<<(ostream& out, const Song& s){
    vector<Voice> voices_vec = s.getVoices();
    int tempo_var = s.getTempo();
    out << tempo_var << "\n"; 
    for(int i = 0; i < voices_vec.size(); i++){
        out << voices_vec.at(i) << "\n"; // printing voices
    }                                    // calls the << of the voice class
        
    return out;
}
ostream& operator<<(ostream& out, const Voice& v){
    vector<Note> test = v.getNotes();

    for(int i = 0; i < test.size(); i++){
        out << test.at(i) << " "; // printing notes
    }                             // calls the << of the note class
    return out;
}
ostream& operator<<(ostream& out, const Note& n){
// here is where almost all the print logic happens 
  switch(n.getPitch()){
    case REST:
      out << "REST";
      break;
    case A:
      out << "A";
      break;
    case B:
      out << "B";
      break;
    case C:
      out << "C";
      break;
    case D:
      out << "D";
      break;
    case E:
      out << "E";
      break;
    case F:
      out << "F";
      break;
    case G:
      out << "G";
      break;
    case Db:
      out << "Db";
      break;
    case Eb:
      out << "Eb";
      break;
    case Gb:
      out << "Gb";
      break;
    case Ab:
      out << "Ab";
      break;
    case Bb:
      out << "Bb";
      break;
  }
  out << n.getOctave();

  if(n.getDuration() == 1.5){
    out << "q.";
  } else if(n.getDuration() == 3.0){
      out << "h.";
  } else if(n.getDuration() == 6.0){
      out << "w.";
  } else if(n.getDuration() == 0.75){
      out << "e.";
  } else if(n.getDuration() == 0.375){
      out << "s.";
  } else if(n.getDuration() == 1.0){
      out << "q";
  } else if(n.getDuration() == 2.0){
      out << "h";
  } else if(n.getDuration() == 4.0){
      out << "w";
  } else if(n.getDuration() == 0.5){
      out << "e";
  } else if(n.getDuration() == 0.25){
      out << "s";
  }
  return out; 
}