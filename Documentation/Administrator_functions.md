##  TIN - Administrator functions documentation

### Available functions for administrator

#### Connect
_connect <"server address:port">_
Connects to server on the specified address (address provided with port). 

#### Sending process
_send_process <"name"> <"path to file">_
User specifies the <"path to the file"> which will be sent to the server. The file should be on the user's machine.
The argument <"name"> is the process's name on the server.

#### Command server to launch process
_launch_process <"name">_
Tells the server to start chosen process

#### Disconnect
_disconnect_
Disconnects from the server

#### Help for user
_help_
Shows the message about available functions

#### Exit
_exit_
Ends administrator process, closes connections
