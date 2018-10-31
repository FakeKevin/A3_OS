/*
Assignment #3 - Question #2
Date Due: Nov. 5th, 2018
By: Jason Han & Keun Young Jee

Description:
Assignment 2, Question 1, involved designing an echo server using the Java threading
API. This server is single-threaded, meaning that the server cannot respond to
concurrent echo clients until the current client exits. Modify your solution to Assignment
2, Question 1, so that the echo server services each client in a separate request.

Input sanitizing - While it is always recommended to sanitize input, the fact that this
program will compile and execute any code it is sent over the Internet basically makes it
impossible to secure properly. Just do basic sanitizing and don’t worry too much.

References:

https://www.geeksforgeeks.org/multithreading-c-2/
https://stackoverflow.com/questions/39122230/multithreading-echo-server
https://stackoverflow.com/questions/42473882/java-multithread-server-to-serve-multiple-concurrent-clients
https://stackoverflow.com/questions/34046833/how-to-alter-a-simple-java-echo-server-to-be-multithreaded
*/

import java.net.*;
import java.io.*;

public class EchoServer {

	private int port = 6013;
	private Socket client;

	public static void main(String[] args) {
		new EchoServer();
	}

	public EchoServer(){
		try {
			ServerSocket sock = new ServerSocket(port);
			System.out.println("Starting server connection on port: " + port);
			// Continuously accept new connections
			while(true) {
			// Start a new thread
				new ClientThreads(sock.accept());
				System.out.println("[Server]: A new client has connected.");
			}

		}catch(IOException ioe){
                System.err.println(ioe);
         }
	}

 private class ClientThreads extends Thread{
	private InputStream in;
	private DataOutputStream out;

    ClientThreads (Socket client) {
		try {
			//Create in and out streams
			in = client.getInputStream();
			out = new DataOutputStream(client.getOutputStream());

			this.start();

			}catch(IOException ioe){
                System.err.println(ioe);
             }
	}

	public void run () {
		try {
			while (true) {
				EchoMessage(in, out);
			}

			}catch(IOException ioe){
			System.err.println(ioe);
			 }
	}
 }

	public void EchoMessage(InputStream in, DataOutputStream out) throws IOException{
	//Create a buffer that will read the input stream
        BufferedReader buffIn = new BufferedReader(new InputStreamReader(in));
        String line = buffIn.readLine();

			//While the client has not entered in nothing:
			while (line != null){
			//Sanitize input
			line = sanitizeInput(line);
			//Print back out at the client exactly what they entered in
			PrintWriter pout = new PrintWriter(out, true);
			pout.println("Server echoes back: "+line);
			line = buffIn.readLine();
			}
	}

    //This function sanitizes input. It will only allow A-Z & a-z,
    //numbers and spaces to be echoed back to the user.
    private static String sanitizeInput(String original)
    {
        String newStr = "";
        String characters = " 1234567890aqwertyuiopsdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";

        //Loop through every character in the original string
        for(int n = 0; n < original.length(); n++)
            {
                String tempChar = original.substring(n, n+1);
                int good = 0;
                //Loop through the good character list. Set a value if we
                //have found a good character
                for (int m = 0; m < characters.length();m++)
                    {
                        if(tempChar.equals(characters.substring(m, m+1)))
                            {
                                good = 1;
                                break;
                            }
                    }
                //Only if that character is good do we add it to the return string
                if(good == 1)
                    {
                        newStr += tempChar;
                    }
            }
        return newStr;
    }
}
