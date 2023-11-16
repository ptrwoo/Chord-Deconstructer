#include <iostream>
#include <unordered_map>
#include <vector>

// note def:
// 1 = C
// 2 = C#
// 3 = D
// 4 = D#
// 5 = E
// 6 = F
// 7 = F#
// 8 = G
// 9 = G#
// 10 = A
// 11 = A#
// 12 = B

struct note
{
    std::string notename;
    std::string intName;
    int notecode;
    int chordtone;
};

std::unordered_map<std::string, int> note_converter = 
{
    {"a", 10},
    {"a#",11},
    {"b", 12},
    {"c", 1},
    {"c#",2},
    {"d", 3},
    {"d#",4},
    {"e", 5},
    {"f", 6},
    {"f#",7},
    {"g", 8},
    {"g#",9},
};

//78 when added all up.
//make c = 13, d = 15 etc..
// c is tonic = 1, e = 5. so 5-1=4, 4 = maj third
// e = 5, g# = 9, diff = 4 so = maj third
// b = 12, d# = 4, diff = 8.. so min sixth - so 4 off..
// a = 10, c# = 2, diff = 8.. so min sixth - diff of 4
// a = 10, c = 1, diff = 9.. so maj sixth - diff of 6
// b = 12, d = 3, diff = 9 .. so maj sixth - diff of 6

std::unordered_map<int, std::string> tone_definer = 
{
    {0, "tonic"},
    {1, "min2"},
    {2, "maj2"},
    {3, "min3"},
    {4, "maj3"},
    {5, "P4"},
    {6, "tritone"},
    {7, "P5"},
    {8, "min6"},
    {9, "maj6"},
    {10, "min7"},
    {11, "maj7"},
    {12, "oct"},
};

class chord
{
    private:
    std::vector<note> thechord;

    public:

   void addNote(const std::string& noteName)
    {
        // Check if the note name is valid
        if(note_converter.find(noteName) != note_converter.end())
        {
            note newNote;
            newNote.notename = noteName;
            newNote.notecode = note_converter[noteName];
            thechord.push_back(newNote);

            std::cout << "added: " << newNote.notename << std::endl;
        }
        else
        {
            std::cerr << "Invalid note name: " << noteName << std::endl;
        }

    }

    void showChord()
    {
        for (note &notes : thechord)
        {
            std::cout << notes.notename;
        }

    }

    void 
    
    setTonic ()
    {
        std::cout << "set tonic note: ";
        std::string tonic;
        std::cin >> tonic;

        if(note_converter.find(tonic) != note_converter.end())
        {
            bool foundTonic = false;

            for(note &n : thechord)
            {
                if(n.notename == tonic)
                {
                    n.chordtone = 1;
                    n.intName = tone_definer[0];
                    foundTonic = true;
                }
                else
                {
                    n.chordtone = 0;
                }
            }

            if(!foundTonic)
            {
                std::cerr << "Note " << tonic << "is not in the chord." << std::endl;
            }
            else
            {
                defineChord();
            }
        }
        else
        {
            std::cerr << "invalid note name: " << tonic << std::endl;
        }

    }

    void defineChord()
{
    int tonicCode = -1;
    for(const note &n : thechord)
    {
        if(n.chordtone == 1)
        {
            tonicCode = n.notecode;
            break;
        }
    }

    if(tonicCode == -1)
    {
        std::cerr << "Tonic not set." << std::endl;
        return;
    }

    for(note &n : thechord)
    {
        if(n.chordtone != 1) // if the note isn't tonic
        {
            int interval = (n.notecode - tonicCode + 12) % 12; 
            if(interval == 0) 
                {
                    interval += 12;
                }

            if(tone_definer.find(interval) != tone_definer.end())
            {
                n.intName = tone_definer[interval];
            }
            else
            {
                std::cerr << "Unexpected interval: " << interval << std::endl;
            }
        }
    }
}

void showtones ()
{
    for(note &n : thechord)
    {
        std::cout << n.notename << " is the " << n.intName << std::endl; 
    }
}

};


int main ()
{

    bool stayOn = true;

    do
    {
        int i;
        std::cout << "1. define chord \n2. exit \n \n";
        std::cin.clear();
        std::cin >> i;
        std::cin.ignore();

        switch (i)
        {

            case 1:
            {
                std::cout << "enter note by note: \n";

                chord thechord;

                std::string x;
                std::string y = "x";
                bool istrue = true;

                while(istrue)
                {
                    std::cin.clear();
                    std::cin >> x;
                    std::cin.ignore();
                    
                    if(x != y)
                    {
                        thechord.addNote(x);
                    }
                    else
                    {
                        std::cout<< "chord entered \n";
                        thechord.showChord();
                        std::cin.get();
                        istrue = false;
                    }
                }
                
                std::cin.get();
                thechord.setTonic();
                thechord.showtones();
                break;
            }

            case 2:
                stayOn = false; 
                break;

            default:
                std::cout << "not a choice. \n";
                break;
        }
    }while(stayOn);

return 0;

}