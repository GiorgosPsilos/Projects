package strategogame.game.board;

/**
 * Representation of a Stratego board.
 */
public class ServerBoard {

    
    private final int numRows = 8;
    private final int numCols = 10;
    private ServerSquare[][] squares;
    
    /**
     * Creates a new instance of Board.
     */
    public ServerBoard() {
        squares = new ServerSquare[numRows][numCols];
        
        for (int row = 0; row < numRows; ++row) {
            for (int col = 0; col < numCols; ++col) {
                squares[row][col] = new ServerSquare();
            }
        }
    }
    
    /**
     * Returns the board square located at (row, col).
     * 
     * @param row board square row
     * @param col board square column
     * @return the square located at (row, col)
     */
    public ServerSquare getSquare(int row, int col) {
        return squares[row][col];
    }
}