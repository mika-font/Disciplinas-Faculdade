public class Carro {
    private String marca;
    private String modelo;
    private int ano;
    private boolean ligado;
    private float velocidade;

    public Carro(String marca, String modelo, int ano) {
        this.marca = marca;
        this.modelo = modelo;
        this.ano = ano;
        this.ligado = false; 
        this.velocidade = 0.0f;
    }

    public void ligar() {
        System.out.println("Ligando o carro...");
        this.ligado = true;
    }

    public void desligar() {
        if (this.velocidade == 0) {
            System.out.println("Desligando o carro...");
            this.ligado = false;
        } else {
            System.out.println("Não é possível desligar o carro em movimento!");
        }
    }

    public void acelerar(float valor) {
        if (!this.ligado) {
            System.out.println("Não é possível acelerar, o carro está desligado.");
            return;
        }

        if (valor > 0) {
            this.velocidade += valor;
            System.out.println("Acelerando... Velocidade atual: " + this.velocidade + " km/h");
        } else {
            System.out.println("Valor inválido. Para acelerar, o valor deve ser positivo.");
        }
    }

    public void frear(float valor) {
        if (!this.ligado) {
            System.out.println("O carro já está desligado e parado.");
            return;
        }

        if (valor > 0) {
            this.velocidade = Math.max(0, this.velocidade - valor);
            System.out.println("Freando... Velocidade atual: " + this.velocidade + " km/h");
            if (this.velocidade == 0) {
                System.out.println("O carro parou.");
            }
        } else {
            System.out.println("Valor inválido. Para frear, o valor deve ser positivo.");
        }
    }
    
    @Override
    public String toString() {
        return "Carro {" +
                "marca='" + marca + '\'' +
                ", modelo='" + modelo + '\'' +
                ", ano=" + ano +
                ", ligado=" + ligado +
                ", velocidade=" + velocidade + " km/h" +
                '}';
    }

    public boolean isLigado() {
        return ligado;
    }
    public float getVelocidade() {
        return velocidade;
    }
    public String getMarca() {
        return marca;
    }
    public String getModelo() {
        return modelo;
    }
    public int getAno() {
        return ano;
    }
    
    public static void main(String[] args) {
        Carro meuCarro = new Carro("Peugeot", "208 Griffe", 2024);
        System.out.println("Status Inicial: " + meuCarro.toString());
        
        System.out.println("\n--- TENTANDO ACELERAR DESLIGADO ---");
        meuCarro.acelerar(50);
        
        System.out.println("\n--- LIGANDO E ACELERANDO ---");
        meuCarro.ligar();
        meuCarro.acelerar(80);
        meuCarro.acelerar(30);
        System.out.println("Status Atual: " + meuCarro.toString());
        
        System.out.println("\n--- TENTANDO DESLIGAR EM MOVIMENTO ---");
        meuCarro.desligar();
        
        System.out.println("\n--- FREANDO ---");
        meuCarro.frear(50);
        System.out.println("Status Atual: " + meuCarro.toString());
        
        System.out.println("\n--- PARANDO O CARRO E DESLIGANDO ---");
        meuCarro.frear(100); 
        meuCarro.desligar();
        System.out.println("Status Final: " + meuCarro.toString());
    }
}