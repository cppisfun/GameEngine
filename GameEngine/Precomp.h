
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


// Secure handling for DirectX memory-related matters

#define SecureDelete(x)  { if (x != nullptr) delete x; x = nullptr; }
#define SecureRelease(x) { if (x != nullptr) x->Release(); x = nullptr; }

#define ShowError(x) { MessageBox(nullptr, x, "Error", MB_OK | MB_ICONERROR); }

#ifdef DEBUG
   #define ShowWarning(x) { MessageBox(nullptr, x, "Warning", MB_OK | MB_ICONWARNING); }
   #define ShowInfo(x)    { MessageBox(nullptr, x, "Information", MB_OK); }
#else
   #define ShowWarning(x)
   #define ShowInfo(x)
#endif


// General definitions

#define ABS             false
#define REL             true

#define ANY             -1
#define NONE            -2

#define LEFT            1
#define RIGHT           2
#define HORIZONTAL      3
#define UP              4
#define DOWN            8
#define VERTICAL        12


// Mouse Buttons

#define LEFT_BUTTON     0
#define MIDDLE_BUTTON   1
#define RIGHT_BUTTON    2
#define BUTTON_COUNT    3

