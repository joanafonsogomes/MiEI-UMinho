public class Main {
    public static void main(String[] args){
        Banco b = new Banco(2); //cria-se um banco com 2 contas

        Cliente1 cliente1 = new Cliente1(b,100,0,5);
        Cliente2 cliente2 = new Cliente2(b,100,0,5);

        //CRIAR AS THREADS
        Thread t1 = new Thread(cliente1);
        Thread t2 = new Thread(cliente2);

        //INICAR AS THREADS
        t1.start();
        t2.start();

        try{
            t1.join();
            t2.join();
        }
        catch(InterruptedException ie){};
    }
}
