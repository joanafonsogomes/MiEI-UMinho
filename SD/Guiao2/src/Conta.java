public class Conta {
    private double saldo;

    public Conta(){
        this.saldo = 0;
    }

    public synchronized void depositar(double valor){
        this.saldo += valor;
    }

    public synchronized void levantar(double valor){
        this.saldo -= valor;
    }

    public synchronized double consultar(){
        return this.saldo;
    }
}
