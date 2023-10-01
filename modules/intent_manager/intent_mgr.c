#include "intent_mgr.h"
#include "dbus_mgr.h"

int process_intent(const char** intent)
{
    send_signal(intent);
}
