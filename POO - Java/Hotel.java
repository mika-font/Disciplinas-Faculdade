public class Hotel {
    private String nome;
    private String localizacao;
    private int quartos;

    public Hotel (){
        //this(new String("Hotel Agostinho Carara"), "Rua dos Andradas", 50);
        nome = "Hotel Agostinho Carara";
        localizacao = new String("Rua dos Andradas");
        quartos = 50;
    }

    public Hotel (String nome, String localizacao, int quartos){
        this.nome = nome;
        this.localizacao = localizacao;
        this.quartos = quartos;
    }

    public void imprimir(){
        String p = nome + "\n" + localizacao + "\n" + quartos + "\n";
        System.out.println(p);
    }

    public static void main(String[] args) {
        Hotel a, b;
        String nome = "Hotelzin do Pneu";
        a = new Hotel(nome, "Uruguaiana", 50);
        b = new Hotel(nome, "Santa Maria", 100);
        a.imprimir();
    }

}