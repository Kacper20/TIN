## TIN - Server documentation

The server serves (ha!) as a link between the system's Administrator and the Nodes. It receives JSON files from the administrator and decides which Node to send them to. It also listens for responses from Nodes which it then passes on to the Administrator.

### Structure
The server is represented by a single class - Server. This class has several private methods responsible for all of its work, with a modest public interface comprised of an initializing constructor and a run method that starts the server up.

It also has two queues (of the type defined in MessageQueue.h) used to pass messages from the admin to the nodes and the other way around.

The four methods that define admin-server-node communication are run in parallel, each in its own thread.

#### Receiving from admin
receiveFromAdmin() first waits for the admin to connect. After that, it sends a notify signal to the thread responsible for sending messages to the admin.
It then enters a loop in which it receives messages from the administrator and puts them into the queue of messages meant for the Nodes (adminNodeQ). The concurrency work, that is accessing the queue correctly, is nicely handled by the MessageQueue class itself.

#### Sending to nodes
sendToNodes() takes a message from the adminNodeQ queue, decides which node to send it to, end proceeds with sending it. Once again, the queue itself handles resource sharing. After sending a command to a node, the server remembers which nodes the processes were assigned to. If the message to send is a command to delete a process, it is sent to the correct node.

#### Receiving from nodes
receiveFromNodes() uses the socket select() function to query all the sockets connected to Nodes and see which ones can be read from. It then iterates through those and puts messages from them into the queue (nodeAdminQ, this time).

#### Sending to admin
sendToAdmin() first checks if the server managed to connect to the admin already. If it didn't, it waits for a signal from receiveFromAdmin(). It's actual job is very simple: it takes messages from the queue (nodeAdminQ) and sends them to the admin.