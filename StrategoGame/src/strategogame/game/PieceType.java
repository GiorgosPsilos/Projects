package strategogame.game;

/**
 * Represents the different Stratego pieces.
 */
public enum PieceType {
    SCOUT(2, 4),
    DWARF(3, 5),
    ELF(4, 2),
    LAVABEAST(5, 2),
    SORCERESS(6, 2),
    BEASTRIDER(7, 3),
    KNIGHT(8, 2),
    MAGE(9, 1),
    DRAGON(10, 1),
    TRAP(-1, 6),
    SLAYER(-1, 1),
    FLAG(-1, 1);
    
    private int value;
    private int count;
    
    /**
     * Creates a new instance of PieceType.
     * 
     * @param value the piece value
     * @param count number of pieces of this type a player has initially
     */
    PieceType(int value, int count) {
        this.value = value;
        this.count = count;
    }
    
    /**
     * @return initial count of piece type
     */
    public int getCount() {
        return count;
    }
    
    /**
     * Returns the result of a battle when one piece type attacks another
     * piece type.
     * 
     * @param defender the defending piece type
     * @return the battle outcome
     */
    public BattleOutcome attack(PieceType defender) {
        // Defender is a flag.
        if (defender == PieceType.FLAG)
            return BattleOutcome.WIN;
        
        // Attacking piece and defending piece are the same piece type.
        else if (this.value == defender.value)
            return BattleOutcome.DRAW;
        
        // Defender is a spy.
        else if (defender == PieceType.SLAYER)
            return BattleOutcome.WIN;

        // Defender is Marshal (10) and Attacker is Spy
        else if(defender == PieceType.DRAGON && this == PieceType.SLAYER) {
        	return BattleOutcome.WIN;
        }
        
        // Defender is a bomb.
        else if (defender == PieceType.TRAP) {
            if (this == PieceType.DWARF)
                return BattleOutcome.WIN;
            else
                return BattleOutcome.LOSE;
        }
        
        // Otherwise, compare piece values.
        else if (this.value > defender.value)
            return BattleOutcome.WIN;
        else
            return BattleOutcome.LOSE;
    }
}