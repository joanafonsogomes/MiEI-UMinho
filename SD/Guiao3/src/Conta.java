import java.util.concurrent.locks.ReentrantLock;

public class Conta {
    private double saldo;
    private ReentrantLock lockConta;

    public Conta(){
        this.saldo = 0;
        this.lockConta = new ReentrantLock();
    }

    public Conta(double saldo) {
        this.saldo = saldo;
    }


    public void depositar(double valor){
        this.saldo += valor;
    }

    public void levantar(double valor){
        this.saldo -= valor;
    }

    public double consultar(){
        return this.saldo;
    }

    public void darLockConta(){
        this.lockConta.lock();
    }

    public void unlockConta(){
        this.lockConta.unlock();
    }
}
