#pragma once

#ifdef _DEBUG
	#define BoolToString(b) ((b) ? "true" : "false")
	#define PrintValInfo(x) {std::cout << "Variable '" << #x << "': " << &x << "[" << BoolToString(x) << "]\n\n";}
	#define PrintPtrInfo(x) {std::cout << "Pointer to object '" << #x << "': " << &x << "[" << x << "]\n\n";}
	#define	PrintArgv(argc) {for (int i = 1; i < argc; i++) { std::cout << "[" << i << "]" << argv[i] << " "; } std::cout << "\n";} 
#endif