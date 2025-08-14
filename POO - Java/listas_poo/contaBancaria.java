package src;

public class contaBancaria {
    private String numeroConta;
    private double saldo;
    private String titular;

    public contaBancaria(String numeroConta, double saldo, String titular){
        this.numeroConta = numeroConta;
        this.saldo = 0.0;
        this.titular = titular;
    }

    public void depositar(double valor) {
        if (valor > 0) {
            this.saldo += valor;
            System.out.println("Depósito de R$ " + valor + " realizado com sucesso.");
            consultarSaldo();
        } else {
            System.out.println("Valor de depósito inválido. Por favor, insira um valor positivo.");
        }
    }

    public void sacar(double valor) {
        if (valor <= 0) {
            System.out.println("Valor de saque inválido.");
        } else if (this.saldo >= valor) {
            this.saldo -= valor;
            System.out.println("Saque de R$ " + valor + " realizado com sucesso.");
            consultarSaldo();
        } else {
            System.out.println("Saque não realizado. Saldo insuficiente.");
        }
    }

    public void transferir(contaBancaria contaDestino, double valor){
        if (valor <= 0) {
            System.out.println("Valor de transferência inválido.");
        } else if (this.saldo >= valor) {
            this.saldo -= valor;
            contaDestino.saldo += valor;
            System.out.println("Transferência de R$ " + valor + " para " + contaDestino.titular + " realizada com sucesso.");
            System.out.println("\n--- Saldo Atualizado ---");
            System.out.print("Sua conta ("+ this.titular +"): ");
            this.consultarSaldo();
            System.out.print("Conta Destino ("+ contaDestino.titular +"): ");
            contaDestino.consultarSaldo();
        } else {
            System.out.println("Transferência não realizada. Saldo insuficiente.");
        }
    }

    public String getTitular() {
        return titular;
    }

    public String getNumeroConta() {
        return numeroConta;
    }

    public void consultarSaldo() {
        System.out.printf("Saldo atual: R$ %.2f%n", this.saldo);
    }
}
