import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class Servidor {

    public static void main(String[] args) throws IOException {

        ServerSocket sSock = new ServerSocket(12345);

        while (true) {
            Socket clSock = sSock.accept();

            BufferedReader in = new BufferedReader(new InputStreamReader(clSock.getInputStream()));

            PrintWriter out = new PrintWriter(clSock.getOutputStream());

            String r;

            while((r=in.readLine())!=null){
                System.out.println(r);
                out.println(r);
                out.flush();
            }

            System.out.println("Saiu.");

            clSock.shutdownOutput();
            clSock.shutdownInput();
            clSock.close();
        }
    }

}
