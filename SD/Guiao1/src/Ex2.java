public class Ex2{

    public static void main(String args[]){

        int N=10;
        int I=100;

        Thread[] threads = new Thread[N];
        Counter c = new Counter();

        //CRIAR INSTANCIAS DE THREADS
        for(int j=0 ; j<N; j++){
            IncrementerRunnable inc =  new IncrementerRunnable();
            threads[j] = new Thread[inc];
        }

        //INICIAR THREADS
        for(int j=0 ; j<N; j++){
            threads[j] =  new NThreads(j);
            threads[j].start();
        }

        //ESPERAR PELA FINALIZAÇÃO DAS THREADS
        for(int j=0 ; j<N; j++){
            threads[j].join();
        }
    }