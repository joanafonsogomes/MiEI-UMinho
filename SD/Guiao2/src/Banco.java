public class Banco {
    private double contas[];

    public Banco(int n){
        this.contas = new double[n];
    }

    public double consultar (int conta){
        return this.contas[conta];
    }

    public synchronized void depositar (int conta, double valor){
        this.contas[conta] += valor;
    }

    public synchronized void levantar (int conta, double valor){
        this.contas[conta] -= valor;
    }

    public void transferir (int contaOr, int contaDest, double valor){
        this.levantar(contaOr,valor);
        this.depositar(contaDest,valor);
    }
}
