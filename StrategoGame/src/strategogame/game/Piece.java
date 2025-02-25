package strategogame.game;

import java.io.Serializable;

/**
 * Represents a single game piece.
 */
public class Piece implements Serializable {

    private static final long serialVersionUID = 7193334048398155856L;
    
    private PieceColor color;
    private PieceType  type;
    
    private boolean isOpponentPiece;
    private String   spriteKey;
    
    /**
     * Creates a new instance of Piece.
     * 
     * @param type PieceType of the piece
     * @param color color of the piece
     * @param isOpponentPiece whether or not the piece belongs to the opponent
     */
    public Piece(PieceType type, PieceColor color, boolean isOpponentPiece) {
        this.isOpponentPiece = isOpponentPiece;
        this.color = color;
        this.type  = type;
        setPieceImage();
    }
    
    /**
     * Sets the Piece's image sprite according to the type of the piece, the 
     * player's color, and whether or not the piece belongs to the opponent.
     */
    private void setPieceImage() {
        if (this.color == PieceColor.RED) {
            switch (type) {
                case SCOUT:      this.spriteKey = "RED_02";   break;
                case DWARF:      this.spriteKey = "RED_03";   break;
                case ELF:   this.spriteKey = "RED_04";   break;
                case LAVABEAST: this.spriteKey = "RED_05";   break;
                case SORCERESS:    this.spriteKey = "RED_06";   break;
                case BEASTRIDER:      this.spriteKey = "RED_07";   break;
                case KNIGHT:    this.spriteKey = "RED_08";   break;
                case MAGE:    this.spriteKey = "RED_09";   break;
                case DRAGON:    this.spriteKey = "RED_10";   break;
                case TRAP:       this.spriteKey = "RED_TRAP"; break;
                case FLAG:       this.spriteKey = "RED_FLAG"; break;
                case SLAYER:        this.spriteKey = "RED_SLAYER";  break;
                default:                                      break;
            }
            
            if (this.isOpponentPiece)
                this.spriteKey = "RED_BACK";
        }
        
        else {
            switch (type) {
                case SCOUT:      this.spriteKey = "BLUE_02";   break;
                case DWARF:      this.spriteKey = "BLUE_03";   break;
                case ELF:   this.spriteKey = "BLUE_04";   break;
                case LAVABEAST: this.spriteKey = "BLUE_05";   break;
                case SORCERESS:    this.spriteKey = "BLUE_06";   break;
                case BEASTRIDER:      this.spriteKey = "BLUE_07";   break;
                case KNIGHT:    this.spriteKey = "BLUE_08";   break;
                case MAGE:    this.spriteKey = "BLUE_09";   break;
                case DRAGON:    this.spriteKey = "BLUE_10";   break;
                case TRAP:       this.spriteKey = "BLUE_TRAP"; break;
                case FLAG:       this.spriteKey = "BLUE_FLAG"; break;
                case SLAYER:        this.spriteKey = "BLUE_SLAYER";  break;
                default:                                       break;
            }
            
            if (this.isOpponentPiece)
                this.spriteKey = "BLUE_BACK";
        }
    }
    
    /**
     * @return the piece type of the piece.
     */
    public PieceType getPieceType() {
        return type;
    }
    
    public PieceColor getPieceColor() {
        return color;
    }
    
    /**
     * @return the sprite associated with the type of the piece.
     */
    public String getPieceSpriteKey() {
        return spriteKey;
    }
}