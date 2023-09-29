/*
    Copyright 2018-2023 Picovoice Inc.

    You may not use this file except in compliance with the license. A copy of the license is located in the "LICENSE"
    file accompanying this source.

    Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on
    an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the
    specific language governing permissions and limitations under the License.
*/
#include <stdio.h>

#include "intent_mgr.h"
#include "mic.h"
#include "dbus_mgr.h"


extern volatile bool is_interrupted;

int main(int argc, char *argv[])
{
    int status = 0;
    setup_microphone(argc, argv);
    status = setup_gdbus();
    printf("Line %d in file %s\n", __LINE__, __FILE__);

    char mic_string[MAX_STR_INTENT_SIZE] = {0};
    while (!is_interrupted && !status)
    {
        retrieve_mic_string(mic_string);
        if (mic_string[0] != '\0')
        {
            process_intent(mic_string);
        }
    }
    printf("\n");

    shutdown_mic();
    return 0;
}
