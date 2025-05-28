import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.SocketTimeoutException;
import java.net.UnknownHostException;

public class UDPClient {
    public static void main(String[] args) {
        String serverHostname = "localhost"; // Or "127.0.0.1"
        int serverPort = 9876;             // Must match the server's port
        byte[] sendBuffer;
        byte[] receiveBuffer = new byte[1024]; // Buffer for server's response

        System.out.println("UDP Client starting...");

        try (DatagramSocket clientSocket = new DatagramSocket(); // Client uses an ephemeral port
             BufferedReader userInputReader = new BufferedReader(new InputStreamReader(System.in))) {

            InetAddress serverIPAddress = InetAddress.getByName(serverHostname);

            System.out.print("Enter a string to reverse (or type 'bye' to quit): ");
            String userInput = userInputReader.readLine();

            if (userInput != null && !userInput.trim().equalsIgnoreCase("bye")) {
                sendBuffer = userInput.getBytes();

                // Create packet to send to server
                DatagramPacket sendPacket = new DatagramPacket(sendBuffer, sendBuffer.length, serverIPAddress, serverPort);

                // Send the packet
                clientSocket.send(sendPacket);
                System.out.println("Sent to server: \"" + userInput + "\"");

                // Prepare packet for receiving server's response
                DatagramPacket receivePacket = new DatagramPacket(receiveBuffer, receiveBuffer.length);

                // Set a timeout for receiving response (e.g., 5 seconds)
                clientSocket.setSoTimeout(5000); // 5000 milliseconds

                // Receive response from server (this call blocks)
                clientSocket.receive(receivePacket);

                String reversedStringFromServer = new String(receivePacket.getData(), 0, receivePacket.getLength()).trim();
                System.out.println("Server responded (reversed): \"" + reversedStringFromServer + "\"");

            } else {
                System.out.println("No input provided or 'bye' entered. Exiting.");
            }

        } catch (SocketTimeoutException e) {
            System.err.println("Timeout: No response from server within 5 seconds.");
        } catch (UnknownHostException e) {
            System.err.println("Error: Unknown host '" + serverHostname + "'.");
        } catch (SocketException e) {
            System.err.println("Socket error on client: " + e.getMessage());
        } catch (IOException e) {
            System.err.println("I/O error on client: " + e.getMessage());
        }
        System.out.println("UDP Client finished.");
    }
}