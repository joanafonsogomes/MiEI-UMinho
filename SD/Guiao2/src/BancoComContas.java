public class BancoComContas {
    private Conta[] contas;

    public BancoComContas(int n){
        this.contas = new Conta[n];
        for(int i=0; i<n; i++){
            contas[i] = new Conta();
        }
    }

    public double consultarConta (int nrConta){
        return this.contas[nrConta].consultar();
    }

    public void depositarConta (int nrConta, double valor){
        this.contas[nrConta].depositar(valor);
    }

    public void levantarConta(int nrConta, double valor){
        this.contas[nrConta].depositar(valor);
    }

    /*public void transferir (int contaOr, int contaDest, double valor){
        this.levantar(contaOr,valor);
        this.depositar(contaDest,valor);
    }*/


}
