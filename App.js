// Importing the necessary components
import Board from './Board';
import Info from "./Info";

// Importing the CSS file
import "./css/app.css";

// Importing the useState hook from React
import { useState } from 'react';

// Creating the main App component
function App() {
  // State for indicating whether the game should be reset
  const [reset, setReset] = useState(false);

  // State for storing the current winner of the game
  const [winner, setWinner] = useState('');

  // Function to trigger the board reset
  const resetBoard = () => {
    setReset(true);
  }

  // Render the App component
  return (
    <div className="App">
      {/* Display the winner popup (shrinks when no winner) */}
      <div className={`winner ${winner !== '' ? '' : 'shrink'}`}>
        {/* Show the name of the current winner */}
        <div className='winner-text'>{winner}</div>
        {/* Button to reset the board */}
        <button onClick={() => resetBoard()}>
          Reset Board
        </button>
      </div>

      {/* Custom-made board component for tic-tac-toe */}
      <Board
        reset={reset}
        setReset={setReset}
        winner={winner}
        setWinner={setWinner}
      />

      {/* Additional component for game information */}
      <Info />
    </div>
  );
}

// Export the App component as the default export
export default App;
