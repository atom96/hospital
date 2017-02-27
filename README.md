Hospital - program which is an imitation of real hospital software, which could be used to store patients medical history.

Author: Arkadiusz Tomczak </br>
Version: 1.0</br>
Date: 03-04-2016</br>
Language:
 - Program language: English
 - Variable names: English
 - Comments: English

Main features (in order to use them you have to write command to stdin):
- Add new disesease to patients medical history: "NEW_DISEASE_ENTER_DESCRIPTION Patient_name Disease_descryption"
- Copy descryption of actual patients disease to anothe patient (maybe there is an epidemy or something like that, so this feature could be useful in this case):
  "NEW_DISEASE_COPY_DESCRIPTION Patient_name_to_copy_to Patient_name_to_copy_From"
- Print descyption of n-th patient disease "PRINT_DESCRIPTION Patient_name disease_number"
- Change descyption of n-th disease "CHANGE_DESCRIPTION Patient_name disease_number new_descryption"
- Delete patients data "DELETE_PATIENT_DATA Patient_name"

Important note: there is no input validation. Yes, tottaly none. It was only an exercise and input validation wasn't neccessary.</br>
As you can see it's not really interesting software, so I do not plan to develp it anymore.
