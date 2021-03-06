
#include <string>

#include <vector>
#include <map>
#include <set>
#include <array>

#include <algorithm>
#include <functional>

#include <exception>
#include <assert.h>

#include <boost/assign.hpp>
#include <boost/lexical_cast.hpp>

#include <Windows.h>


// Type definitions for general use

typedef std::vector<char> Binary;


// Message boxes

#define ShowError(x) { MessageBox(nullptr, x, "Error", MB_OK | MB_ICONERROR); }

#ifdef DEBUG
   #define ShowWarning(x) { MessageBox(nullptr, x, "Warning", MB_OK | MB_ICONWARNING); }
   #define ShowInfo(x)    { MessageBox(nullptr, x, "Information", MB_OK); }
#else
   #define ShowWarning(x)
   #define ShowInfo(x)
#endif


// Secure handling for DirectX memory-related matters (deprecation awaits you)

#define SecureDelete(x)  { if (x != nullptr) delete x; x = nullptr; }
#define SecureRelease(x) { if (x != nullptr) x->Release(); x = nullptr; }

