#include <fstream>
#include <iostream>
#include <vector>
#include <sys/time.h>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdlib.h> 
#include "mtimer.h"

using namespace std;

class ZTimer
{ 
public:
    struct timeval t1, t2;
public:
    ZTimer() { gettimeofday(&t1,0); t2 = t1; }
    void reset() {gettimeofday(&t1,0); t2 = t1;} 
    long elapsed() { return ((t2.tv_sec - t1.tv_sec) * 1000) + ((t2.tv_usec - t1.tv_usec) / 1000); }
    long split() { gettimeofday(&t2,0); return elapsed(); }
};


class CSVParser {
public:
    CSVParser(istream & in, ostream& os, const int& bin_sz = 20, const string delimiter =  "\t", 
	      const char  commentmarker= '#'); 
    virtual ~CSVParser() {}
    bool readWithoutParsing() {
	return getline(mIn,line); 
    }
    
    bool hasNext(int& currPos, char* currChr, float& currVal, float& currDelta) {

        char chr[20];
	int start,end;
	float val;    

	while(getline(mIn,line)) {
	    if(line.size() == 0) continue;
	    if(line.at(0) == mCommentMarker) continue;
    
	    sscanf(line.c_str(), fmt, chr, &start, &end, &val);
	    

	    if (strcmp(chr,currChr) != 0)
	    {
		currPos = start-start%bin;
		strcpy(currChr, chr);
	    }
	    
	    int curr = start-start%bin;
	    int last = end+bin-end%bin;
	    int nbr = (last-curr)/bin;
	    int next = curr+bin;
	    //cout<<"currentPos "<<currPos<<". ";
	    for (int i = 0; i < nbr; i++)
	    {
		curr = max(curr, start);
		next = min(next, end);

		int delta = next-curr;
		int pos = curr-curr%bin;

		if(pos==currPos)
		{
		    currDelta += delta;
		    currVal += val*delta;
		}
		else {
		    float v = (currVal/currDelta);
		    mOut<<chr<<","<<currPos<<","<<(currPos+bin)<<","<<v<<endl;
			
		    currDelta = delta;
		    currVal = val*delta;
		    currPos = pos;
		}
		curr = next;
		next += bin;		    
	    }	    
	    		
	    return true;
	}
	mOut<<chr<<","<<currPos<<","<<(currPos+bin)<<","<<(currVal/currDelta)<<endl;
		
	return false;
     }
    
    const vector<string> & next()  const {
	return currentData;
    }


protected:
    
    string line;

    inline void tokenize(const string& str);
    inline void parse_line(const string& line);
    //proj inline project(const *chr, const int& start, const int&end, const float& val);
    string mDelimiter;
    string mDelimiterPlusSpace;
    char mCommentMarker;
    
    istream & mIn;
    ostream& mOut;

    char fmt[250];
    vector<string> currentData;

    int bin;

};


CSVParser::CSVParser(istream & in, ostream& os, const int& bin,
		     const string delimiter, const char  commentmarker) : 
	line(), mDelimiter(delimiter), 
	mDelimiterPlusSpace(delimiter),
	mCommentMarker( commentmarker),
	mIn(in),
	mOut(os),
	currentData(), bin(bin)
{
	mDelimiterPlusSpace.append(" ");
	const char *cstr = mDelimiter.c_str();
	sprintf(fmt, "%%s%s%%d%s%%d%s%%f%s", cstr, cstr, cstr, cstr);
}



void CSVParser::tokenize(const string& str){
        size_t counter(0);
    	string::size_type lastPos = str.find_first_not_of(mDelimiterPlusSpace, 0);
    	string::size_type pos     = str.find_first_of(mDelimiter, lastPos);
	string::size_type pos_w = str.find_last_not_of(' ',pos);
    	while (string::npos != pos || string::npos != lastPos) {
    		const string::size_type fieldlength = pos == string::npos ?   pos_w + 1 - lastPos: pos_w -lastPos;
            if(currentData.size() < ++counter) currentData.resize(counter);
            currentData[counter-1].resize(fieldlength);
            currentData[counter-1].assign(str,lastPos, fieldlength);
        	lastPos = str.find_first_not_of(mDelimiterPlusSpace, pos);
        	pos = str.find_first_of(mDelimiter, lastPos);
        	pos_w = str.find_last_not_of(' ',pos);
    	}
	currentData.resize(counter);
//        project(currentData);
}


void CSVParser::parse_line(const string& line)
{

}


void parseCSV(char* csvfile, char* csvOut, int bin_sz) {
    ifstream in(csvfile);
    ofstream out(csvOut);
    CSVParser csvp(in, out, bin_sz);

    char currChr[20];
    int currPos = 0;
    float currDelta = 0.0;
    float currVal = 0.0;
    
    long lineNbr = 0;

    while(csvp.hasNext(currPos, currChr, currVal, currDelta)) {
	csvp.next();
	lineNbr++;
    }	
    cout<<"processed "<<lineNbr<<" lines. ";
    in.close();
    out.flush();
    out.close();
}



void readCSVwithoutParsing(string & csvfile) {
	ifstream in(csvfile.c_str());
	ofstream out("~/tmp/out.csv");
	CSVParser csvp(in, out, 20);
	while(csvp.readWithoutParsing()) {
	}
	in.close();
}

int fibonacci(int n)
{
     if ( n == 0 ) 
        return 0;
     if ( n == 1 ) 
        return 1;
 
     return fibonacci(n-1) + fibonacci(n-2);
}

int main() {

	ZTimer timer;
	ExTimer mtimer;
	for (size_t i = 0; i < 20; i++) {
	  for (size_t j = 0; j < 20; j++) {
	    size_t k = fibonacci(i+j);
	  }
	}
        
	cout << " time taken... (by ZTimer) "<< timer.split()/1000.0 << endl;
	cout << " time taken... (by MTimer) "<< mtimer.getElapsedTime()/1000000<<endl;
}
