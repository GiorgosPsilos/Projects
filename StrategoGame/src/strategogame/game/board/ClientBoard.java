package strategogame.game.board;

import strategogame.gui.board.BoardEventPane;
import strategogame.gui.board.BoardPane;
import strategogame.gui.board.BoardSquareType;

/**
 * Representation of a Stratego board.
 */
public class ClientBoard {

    private final BoardPane piecePane;
    private final BoardEventPane eventPane;
    private final int numRows = 8;
    private final int numCols = 10;
    private ClientSquare[][] squares;
    
    /**
     * Creates a new instance of Board.
     */
    public ClientBoard() {
        // Initialize the board GUI.
        squares = new ClientSquare[numRows][numCols];
        for (int row = 0; row < numRows; ++row) {
            for (int col = 0; col < numCols; ++col) {
                if ((row + col) % 2 == 0)
                    squares[row][col] = new ClientSquare(BoardSquareType.DARK);
                else
                    squares[row][col] = new ClientSquare(BoardSquareType.LIGHT);
            }
        }
        
        // Initialize board layers.
        piecePane = new BoardPane(this);
        eventPane = new BoardEventPane(this);
    }
    
    /**
     * Returns the board square located at (row, col).
     * 
     * @param row board square row
     * @param col board square column
     * @return the square located at (row, col)
     */
    public ClientSquare getSquare(int row, int col) {
        return squares[row][col];
    }
    
    /**
     * @return the BoardPane.
     */
    public BoardPane getPiecePane() {
        return piecePane;
    }
    
    /**
     * @return the BoardEventPane.
     */
    public BoardEventPane getEventPane() {
        return eventPane;
    }
}