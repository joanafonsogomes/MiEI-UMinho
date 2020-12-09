import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.locks.ReentrantLock;

public class Banco {
    private Map<Integer, Conta> contas;
    private ReentrantLock lockBanco;
    private int lastID;

    public Banco() {
        this.contas = new HashMap<Integer, Conta>();
        int i;
        for (i = 0; i < 10; i++) {
            Conta c = new Conta();
            this.contas.put(i, c);
        }
        lastID = i - 1;
        this.lockBanco = new ReentrantLock();
    }

    public int criarConta(double saldoInicial){
        this.lockBanco.lock();
        int id = lastID++;
        Conta c = new Conta(saldoInicial);
        this.contas.put(id,c);
        this.lockBanco.unlock();

        return id;
    }

    public double fecharConta(int idConta) throws ContaInvalida{
        this.lockBanco.lock();

        if (!contas.containsKey(idConta)) {
            lockBanco.unlock();
            throw new ContaInvalida("Está a tentar fechar uma conta que não existe.");
        }

        this.contas.get(idConta).darLockConta();

        double s = this.contas.get(idConta).consultar();
        this.contas.remove(idConta);
        this.contas.get(idConta).unlockConta();

        this.lockBanco.unlock();

        return s;
    }

    /*public double fecharConta(int idConta) throws ContaInvalida{

    }*/

    public double consultarTotal(int idsContas[]) {
        double res = 0;
        for (int i = 0; i < idsContas.length; i++) {
            res += this.contas.get(i).consultar();
        }
        return res;
    }

    public double consultaConta(int idConta) throws ContaInvalida {
        lockBanco.lock();
        if (!contas.containsKey(idConta)) {
            lockBanco.unlock();
            throw new ContaInvalida("Este ID de conta não é válido.");
        }
        this.contas.get(idConta).darLockConta();
        lockBanco.unlock();

        double r = contas.get(idConta).consultar();
        this.contas.get(idConta).unlockConta();

        return r;
    }

    public void levantar(int idConta, double valor) throws ContaInvalida, SaldoInsuficiente {
        lockBanco.lock();

        if (!contas.containsKey(idConta)) {
            lockBanco.unlock();
            throw new ContaInvalida("Este ID de conta não é válido.");
        }

        this.contas.get(idConta).darLockConta();
        lockBanco.unlock();
        double s = this.contas.get(idConta).consultar();
        if (valor > s) {
            this.contas.get(idConta).unlockConta();
            throw new SaldoInsuficiente("Não tem o valor dísponível para levantar.");
        }
        this.contas.get(idConta).levantar(valor);
        this.contas.get(idConta).unlockConta();
    }

    public void depositar(int idConta, double valor) throws ContaInvalida {
        lockBanco.lock();

        if (!contas.containsKey(idConta)) {
            lockBanco.unlock();
            throw new ContaInvalida("Este ID de conta não é válido.");
        }

        this.contas.get(idConta).darLockConta();
        lockBanco.unlock();

        this.contas.get(idConta).depositar(valor);
        this.contas.get(idConta).unlockConta();
    }

    public void transferir(int contaOr, int contaDest, double valor) throws ContaInvalida, SaldoInsuficiente {
        lockBanco.lock();

        if ((!contas.containsKey(contaOr)) || (!contas.containsKey(contaDest))) {
            lockBanco.unlock();
            throw new ContaInvalida("Inseriu ID inválido.");
        }

        this.contas.get(contaOr).darLockConta();
        this.contas.get(contaDest).darLockConta();

        lockBanco.unlock();

        this.contas.get(contaOr).levantar(valor);
        this.contas.get(contaDest).depositar(valor);

        this.contas.get(contaOr).unlockConta();
        this.contas.get(contaDest).unLockConta();
    }

}