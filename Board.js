// Import the CSS styles for the board component
import "./css/board.css";

// Import necessary React hooks
import { useState, useEffect, useRef } from "react";

// Define the Board component
const Board = ({ reset, setReset, winner, setWinner }) => {
  // State to track the current player's turn
  const [turn, setTurn] = useState(0);

  // State to store the current state of the board
  const [data, setData] = useState([
    '', '', '', '', '', '', '', '', ''
  ]);

  // Create a reference to the board element
  const boardRef = useRef(null);

  // Function to handle player moves and update the board
  const draw = (event, index) => {
    // Allow drawing only if the cell is empty and there's no winner
    if (data[index - 1] === '' && winner === '') {
      // Determine whether to draw 'X' or 'O'
      const current = turn === 0 ? "X" : "O";

      // Update the data state
      data[index - 1] = current;

      // Draw 'X' or 'O' on the board
      event.target.innerText = current;

      // Switch to the next player's turn
      setTurn(turn === 0 ? 1 : 0);
    }
  }

  // UseEffect hook to reset the board when necessary
  useEffect(() => {
    // Clear the data state
    setData(['', '', '', '', '', '', '', '', '']);

    // Clear the cells on the board
    const cells = boardRef.current.children;
    for (let i = 0; i < 9; i++) {
      cells[i].innerText = '';
    }

    // Reset the turn to Player 1's turn
    setTurn(0);

    // Reset the winner and the reset flag
    setWinner('');
    setReset(false);
  }, [reset, setReset, setWinner]);

  // UseEffect hook to check for a winner or tie
  useEffect(() => {
    // Helper functions to check for win conditions
    const checkRow = () => {
      for (let i = 0; i < 9; i += 3) {
        if (data[i] === data[i + 1] && data[i] === data[i + 2] && data[i] !== '') {
          return true;
        }
      }
      return false;
    }

    const checkCol = () => {
      for (let i = 0; i < 3; i++) {
        if (data[i] === data[i + 3] && data[i] === data[i + 6] && data[i] !== '') {
          return true;
        }
      }
      return false;
    }

    const checkDiagonal = () => {
      return (data[0] === data[4] && data[0] === data[8] && data[0] !== '') ||
             (data[2] === data[4] && data[2] === data[6] && data[2] !== '');
    }

    const checkWin = () => {
      return checkRow() || checkCol() || checkDiagonal();
    }

    const checkTie = () => {
      return data.every(cell => cell !== ''); // Checks if the board is full
    }

    // Determine the winner or if it's a tie
    if (checkWin()) {
      setWinner(turn === 0 ? "Player 2 Wins!" : "Player 1 Wins!"); // Turn 0 is player 1's turn
    } else if (checkTie()) {
      setWinner("It's a Tie!");
    }
  });

  // Render the board with clickable cells
  return (
    <div ref={boardRef} className="board">
      {Array.from({ length: 9 }, (_, index) => (
        <div
          key={index}
          className={`input input-${index + 1}`}
          onClick={(e) => draw(e, index + 1)}
        ></div>
      ))}
    </div>
  );
}

// Export the Board component
export default Board;
