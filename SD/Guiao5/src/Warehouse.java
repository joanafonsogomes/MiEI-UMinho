import java.util.HashMap;
import java.util.Map;

public class Warehouse {

    private HashMap<String,Item> stock;

    public Warehouse(String[] items){
        this.stock = new HashMap<>();
        for(String i : items){
            this.stock.put(i,new Item(1,0));
        }
    }

    //abastecer um armazém com uma dada quantidade de um item
    public void supply(String item, int quantity) throws InterruptedException {
        if(!stock.containsKey(item)){
            Item i = new Item();
            this.stock.put(item,i);
        }
        this.stock.get(item).supply(quantity);
        System.out.println("Item: " + item + "  Stock increased: " + quantity);
    }

    //obter do armazém um conjunto de itens, bloqueando enquanto tal não for possível
    public void consume(String[] items) throws InterruptedException {
        for(String i : items){
            if(this.stock.containsKey(i)) {
                this.stock.get(i).consume();
                System.out.println("Item: " + i + "  Stock decreased");
            }
        }
    }

}