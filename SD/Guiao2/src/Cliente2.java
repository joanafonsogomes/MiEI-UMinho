public class Cliente2 implements Runnable{

    //VARIAVEIS DE INSTANCIA
    private Banco b;
    private int nrVezes;
    private int nrConta;
    private double valor;

    //METODO RUN
    public void run(){
        for(int i=0; i<nrVezes; i++){
            this.b.levantar(this.nrConta,this.valor);
            System.out.println("Cliente 2 levantou 5 euros.");
        }
    }

    public Cliente2(Banco b, int nrVezes, int nrConta, double valor){
        this.b = b;
        this.nrVezes = nrVezes;
        this.nrConta = nrConta;
        this.valor = valor;
    }

}
