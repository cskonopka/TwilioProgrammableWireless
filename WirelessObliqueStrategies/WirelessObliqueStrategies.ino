#include "wio_tracker.h"

// Define the number of elements in a string-based array
#define NUMITEMS(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0])))

uint16_t newSMSNumber = -1;
char phone[32];
char dateTime[32];
char message[128];

WioTracker wio = WioTracker();

// put your setup code here, to run once:
//https://forum.arduino.cc/index.php?topic=157398.0

// Oblique Strategies [Edition 1]
String obliquestrategies[] = {
  "Abandon normal instruments",
  "Accept advice",
  "Accretion",
  "A line has two sides",
  "Allow an easement (an easement is the abandonment of a stricture)",
  "Are there sections? Consider transitions",
  "Ask people to work against their better judgement",
  "Ask your body",
  "Assemble some of the instruments in a group and treat the group",
  "Balance the consistency principle with the inconsistency principle",
  "Be dirty",
  "Breathe more deeply",
  "Bridges -build -burn",
  "Cascades",
  "Change instrument roles",
  "Change nothing and continue with immaculate consistency",
  "Children's voices -speaking -singing",
  "Cluster analysis",
  "Consider different fading systems",
  "Consult other sources -promising -unpromising",
  "Convert a melodic element into a rhythmic element",
  "Courage!",
  "Cut a vital connection",
  "Decorate, decorate",
  "Define an area as 'safe' and use it as an anchor",
  "Destroy -nothing -the most important thing",
  "Discard an axiom",
  "Disconnect from desire",
  "Discover the recipes you are using and abandon them",
  "Distorting time",
  "Do nothing for as long as possible",
  "Don't be afraid of things because they're easy to do",
  "Don't be frightened of cliches",
  "Don't be frightened to display your talents",
  "Don't break the silence",
  "Don't stress one thing more than another",
  "Do something boring",
  "Do the washing up",
  "Do the words need changing?",
  "Do we need holes?",
  "Emphasise differences",
  "Emphasise repetitions",
  "Emphasise the flaws",
  "Faced with a choice, do both (given by Dieter Rot)",
  "Feedback recordings into an acoustic situation",
  "Fill every beat with something",
  "Get your neck massaged",
  "Ghost echoes",
  "Give the game away",
  "Give way to your worst impulse",
  "Go slowly all the way round the outside",
  "Honor thy error as a hidden intention",
  "How would you have done it?",
  "Humanise something free of error",
  "Imagine the music as a moving chain or caterpillar",
  "Imagine the music as a set of disconnected events",
  "Infinitesimal gradations",
  "Intentions -credibility of -nobility of -humility of",
  "Into the impossible",
  "Is it finished?",
  "Is there something missing?",
  "Is the tuning appropriate?",
  "Just carry on",
  "Left channel, right channel, centre channel",
  "Listen in total darkness, or in a very large room, very quietly",
  "Listen to the quiet voice",
  "Look at a very small object, look at its centre",
  "Look at the order in which you do things",
  "Look closely at the most embarrassing details and amplify them",
  "Lowest common denominator check -single beat -single note -single riff",
  "Make a blank valuable by putting it in an exquisite frame",
  "Make an exhaustive list of everything you might do and do the last thing on the list",
  "Make a sudden, destructive unpredictable action; incorporate",
  "Mechanicalise something idiosyncratic",
  "Mute and continue",
  "Only one element of each kind",
  "(Organic) machinery",
  "Overtly resist change",
  "Put in earplugs",
  "Remember .those quiet evenings",
  "Remove ambiguities and convert to specifics",
  "Remove specifics and convert to ambiguities",
  "Repetition is a form of change",
  "Reverse",
  "Short circuit (example; a man eating peas with the idea that they will improve his virility shovels them straight into his lap)",
  "Shut the door and listen from outside",
  "Simple subtraction",
  "Spectrum analysis",
  "Take a break",
  "Take away the elements in order of apparent non-importance",
  "Tape your mouth (given by Ritva Saarikko)",
  "The inconsistency principle",
  "The tape is now the music",
  "Think of the radio",
  "Tidy up",
  "Trust in the you of now",
  "Turn it upside down",
  "Twist the spine",
  "Use an old idea",
  "Use an unacceptable colour",
  "Use fewer notes",
  "Use filters",
  "Use 'unqualified' people",
  "Water",
  "What are you really thinking about just now? Incorporate",
  "What is the reality of the situation?",
  "What mistakes did you make last time?",
  "What would your closest friend do?",
  "What wouldn't you do?",
  "Work at a different speed",
  "You are an engineer",
  "You can only make one dot at a time",
  "You don't have to be ashamed of using your own ideas"
};

int globalArraySize = NUMITEMS(obliquestrategies);
void setup() {
  wio.Power_On();
  SerialUSB.println("Power On!");
  SerialUSB.println("Wait for network registered...");

  if (!wio.waitForNetworkRegister())
  {
    SerialUSB.println("Network error!");
    return;
  } else {
    SerialUSB.println("Network ready!");
  }
  wio.readAllRecUnreadSMS();  // Set all "REC UNREAD SMS" to "REC READ SMS"
}

void loop() {
  char osBuffer[50];
  int id = wio.detectRecUnreadSMS();
  if (-1 != id) {
    newSMSNumber = id;
    wio.readSMS(newSMSNumber, message, 128, phone, dateTime);
    SerialUSB.println("++++++++++++++ Start +++++++++++++++++");
    SerialUSB.print("From: ");
    SerialUSB.println(phone);
    SerialUSB.print("Date: ");
    SerialUSB.println(dateTime);
    SerialUSB.println(message);
    SerialUSB.println("++++++++++++++++ End +++++++++++++++");
    SerialUSB.println("++++++++ SENDING SMS +++++++++++++++");
    delay(100);
    SerialUSB.println("Drawing New Card +++++++++++++++++++");
    long randNumber = random(globalArraySize);
    SerialUSB.println(obliquestrategies[randNumber]);
    obliquestrategies[randNumber].toCharArray(osBuffer, 50);
    if (wio.sendSMS(phone, osBuffer))
    {
      SerialUSB.println("Send OK!");
    }
    else
    {
      SerialUSB.println("Send Error!");
    }
  } else {
    SerialUSB.println("Waiting for new SMS!");
  }
  delay(1000);
}
