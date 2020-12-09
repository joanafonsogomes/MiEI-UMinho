public class Cliente1 implements Runnable{

    //VARIAVEIS DE INSTANCIA
    private Banco b;
    private int nrVezes;
    private int nrConta;
    private double valor;

    //METODO RUN
    public void run(){
        for(int i=0; i<nrVezes; i++){
            this.b.depositar(this.nrConta,this.valor);
            System.out.println("Cliente 1 depositou 5 euros.");
        }
    }

    public Cliente1(Banco b, int nrVezes, int nrConta, double valor){
        this.b = b;
        this.nrVezes = nrVezes;
        this.nrConta = nrConta;
        this.valor = valor;
    }

}
