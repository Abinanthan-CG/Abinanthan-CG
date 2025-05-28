import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;

public class UDPServer {

    public static String reverseString(String input) {
        if (input == null) {
            return null;
        }
        return new StringBuilder(input).reverse().toString();
    }

    public static void main(String[] args) {
        int serverPort = 9876; // You can choose any available port
        byte[] receiveBuffer = new byte[1024]; // Buffer for incoming data
        byte[] sendBuffer;                     // Buffer for outgoing data

        System.out.println("UDP Server starting on port " + serverPort + "...");

        try (DatagramSocket serverSocket = new DatagramSocket(serverPort)) {
            System.out.println("Server is listening...");

            while (true) { // Keep server running to handle multiple client requests
                // Prepare packet for receiving data
                DatagramPacket receivePacket = new DatagramPacket(receiveBuffer, receiveBuffer.length);

                // Receive data from client (this call blocks until a packet is received)
                serverSocket.receive(receivePacket);

                // Extract data and client details from the received packet
                String clientString = new String(receivePacket.getData(), 0, receivePacket.getLength()).trim();
                InetAddress clientAddress = receivePacket.getAddress();
                int clientPort = receivePacket.getPort();

                System.out.println("Received from [" + clientAddress.getHostAddress() + ":" + clientPort + "]: \"" + clientString + "\"");

                // Process the received string (reverse it)
                String reversedString = reverseString(clientString);

                // Prepare the response packet
                sendBuffer = reversedString.getBytes();
                DatagramPacket sendPacket = new DatagramPacket(sendBuffer, sendBuffer.length, clientAddress, clientPort);

                // Send the reversed string back to the client
                serverSocket.send(sendPacket);
                System.out.println("Sent reversed string to client: \"" + reversedString + "\"");

                // Clear the receive buffer for the next iteration (optional, but good practice)
                // receiveBuffer = new byte[1024]; // Not strictly necessary as DatagramPacket is re-used
            }
        } catch (SocketException e) {
            System.err.println("SocketException on server: " + e.getMessage());
            e.printStackTrace();
        } catch (IOException e) {
            System.err.println("IOException on server: " + e.getMessage());
            e.printStackTrace();
        }
    }
}