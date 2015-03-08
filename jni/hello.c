#include <jni.h>
#include "hello.h"
#include <stdio.h>
#include <map>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <memory>
#include "CodeObject.h"
#include "CFG.h"

using namespace std;
using namespace Dyninst;
using namespace ParseAPI;

JNIEXPORT void JNICALL Java_hello_sayHello
	(JNIEnv * env, jobject obj, jstring javaString)
{
	char *nativeString = (char*) (env)->GetStringUTFChars(javaString, 0);
	printf("\nI'M ALIVE!!: parsing %s...\n", nativeString);

	vector<Function *> funcs;
	SymtabCodeSource *sts;
	CodeObject *co;
	CodeRegion *cr;

	sts = new SymtabCodeSource(nativeString);
	co = new CodeObject(sts);

	//parse the binary given as a command line arg
	co->parse();

	//get list of all functions in the binary
	const CodeObject::funclist &all = co->funcs();

	//iterate the ContainerWrapper
	auto fit = all.begin();
	for(int i=0; fit != all.end(); ++fit, i++){
		Function *f = *fit;
		cout << "{address: \"" << hex << f->addr() << "\", name: \"" << f->name() << "\"}," << endl;
	}
}
