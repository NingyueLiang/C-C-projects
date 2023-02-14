
# multiAgents.py
# --------------
# Licensing Information: Please do not distribute or publish solutions to this
# project. You are free to use and extend these projects for educational
# purposes. The Pacman AI projects were developed at UC Berkeley, primarily by
# John DeNero (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# For more info, see http://inst.eecs.berkeley.edu/~cs188/sp09/pacman.html

from util import manhattanDistance
from game import Directions
import random, util

from game import Agent

class ReflexAgent(Agent):
  """
    A reflex agent chooses an action at each choice point by examining
    its alternatives via a state evaluation function.

    The code below is provided as a guide.  You are welcome to change
    it in any way you see fit, so long as you don't touch our method
    headers.
  """


  def getAction(self, gameState):
    """
    You do not need to change this method, but you're welcome to.

    getAction chooses among the best options according to the evaluation function.

    Just like in the previous project, getAction takes a GameState and returns
    some Directions.X for some X in the set {North, South, West, East, Stop}
    """
    # Collect legal moves and successor states
    legalMoves = gameState.getLegalActions()

    # Choose one of the best actions
    scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
    bestScore = max(scores)
    bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
    chosenIndex = random.choice(bestIndices) # Pick randomly among the best

    "Add more of your code here if you want to"

    return legalMoves[chosenIndex]

  def evaluationFunction(self, currentGameState, action):
    """
    Design a better evaluation function here.

    The evaluation function takes in the current and proposed successor
    GameStates (pacman.py) and returns a number, where higher numbers are better.

    The code below extracts some useful information from the state, like the
    remaining food (newFood) and Pacman position after moving (newPos).
    newScaredTimes holds the number of moves that each ghost will remain
    scared because of Pacman having eaten a power pellet.

    Print out these variables to see what you're getting, then combine them
    to create a masterful evaluation function.
    """
    # Useful information you can extract from a GameState (pacman.py)
    successorGameState = currentGameState.generatePacmanSuccessor(action)
    newPos = successorGameState.getPacmanPosition()
    newFood = successorGameState.getFood()
    newGhostStates = successorGameState.getGhostStates()
    newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]

    "*** YOUR CODE HERE ***"
    foodDist = []
    ghostDist = []


    for ghost in newGhostStates:
      if util.manhattanDistance(ghost.getPosition(), newPos) < 2:
        return float(-1000000)
      else:
        ghostDist.append(util.manhattanDistance(ghost.getPosition(), newPos))

    if newPos in currentGameState.getFood().asList():
        return float(1000000)

    for foodpos in newFood.asList():
      foodDist.append(util.manhattanDistance(newPos, foodpos))


    foodscore = 0
    if len(foodDist)>0:
      foodscore = min(foodDist) * 8

    ghostscore = 0
    if len(ghostDist)>0:
      ghostscore = min(ghostDist) * 2

    return  successorGameState.getScore() + ghostscore - foodscore

def scoreEvaluationFunction(currentGameState):
  """
    This default evaluation function just returns the score of the state.
    The score is the same one displayed in the Pacman GUI.

    This evaluation function is meant for use with adversarial search agents
    (not reflex agents).
  """
  return currentGameState.getScore()

class MultiAgentSearchAgent(Agent):
  """
    This class provides some common elements to all of your
    multi-agent searchers.  Any methods defined here will be available
    to the MinimaxPacmanAgent, AlphaBetaPacmanAgent & ExpectimaxPacmanAgent.

    You *do not* need to make any changes here, but you can if you want to
    add functionality to all your adversarial search agents.  Please do not
    remove anything, however.

    Note: this is an abstract class: one that should not be instantiated.  It's
    only partially specified, and designed to be extended.  Agent (game.py)
    is another abstract class.
  """

  def __init__(self, evalFn = 'scoreEvaluationFunction', depth = '2'):
    self.index = 0 # Pacman is always agent index 0
    self.evaluationFunction = util.lookup(evalFn, globals())
    self.depth = int(depth)

class MinimaxAgent(MultiAgentSearchAgent):
  """
    Your minimax agent (question 2)
  """

  def getAction(self, gameState):
    """
      Returns the minimax action from the current gameState using self.depth
      and self.evaluationFunction.

      Here are some method calls that might be useful when implementing minimax.

      gameState.getLegalActions(agentIndex):
        Returns a list of legal actions for an agent
        agentIndex=0 means Pacman, ghosts are >= 1

      Directions.STOP:
        The stop direction, which is always legal

      gameState.generateSuccessor(agentIndex, action):
        Returns the successor game state after an agent takes an action

      gameState.getNumAgents():
        Returns the total number of agents in the game
    """
    "*** YOUR CODE HERE ***"
    #at depth 0 & agentIndex = 0
    v = float('-inf')
    chooseAction = gameState.getLegalActions(0)[0]
    for action in gameState.getLegalActions(0):
      if self.value(gameState.generateSuccessor(0, action), 0, 1) > v:
        v = self.value(gameState.generateSuccessor(0, action), 0, 1)
        chooseAction = action

    return chooseAction

  def maxValue(self,gameState,depth,agentIndex):
      v = float('-inf')  #initialize the max value
      for action in gameState.getLegalActions(0):
        v = max(v, self.value(gameState.generateSuccessor(0, action), depth, 1))

      return v

  def minValue(self,gameState,depth,ghostIndex):
      v = float('inf') #initialize the min value
      for action in gameState.getLegalActions(ghostIndex):
        if ghostIndex == gameState.getNumAgents()-1 :
          v = min(v, self.value(gameState.generateSuccessor(ghostIndex, action), depth+1, 0))  #to further depth

        else:
          v = min(v,self.value(gameState.generateSuccessor(ghostIndex, action), depth, ghostIndex+1))  #iterate through all the ghost agents

      return v

  def value(self,gameState, depth, agentIndex):
      if gameState.isWin() or gameState.isLose() or depth == self.depth: #chech if it's a terminal state
        return self.evaluationFunction(gameState)

      if agentIndex == 0:
        return self.maxValue(gameState,depth,agentIndex)
      else:
        return self.minValue(gameState,depth,agentIndex)

class AlphaBetaAgent(MultiAgentSearchAgent):
  """
    Your minimax agent with alpha-beta pruning (question 3)
  """

  def getAction(self, gameState):
    """
      Returns the minimax action using self.depth and self.evaluationFunction
    """
    "*** YOUR CODE HERE ***"
    # at depth 0 & agentIndex = 0
    v = float('-inf')
    chooseAction = gameState.getLegalActions(0)[0]
    for action in gameState.getLegalActions(0):
        new_v = self.value(gameState.generateSuccessor(0, action), 0, 1, float('-inf'), float('inf'))
        if new_v > v:
            v = new_v
            chooseAction = action

    return chooseAction

  def value(self, gameState, depth, agentIndex, alpha, beta):
      if gameState.isWin() or gameState.isLose() or depth == self.depth:  # chech if it's a terminal state
          return self.evaluationFunction(gameState)

      if agentIndex == 0:
          return self.maxValue(gameState, depth, agentIndex, float(alpha), float(beta))
      else:
          return self.minValue(gameState, depth, agentIndex, float(alpha), float(beta))

  def maxValue(self, gameState, depth, agentIndex, alpha, beta):
      v = float('-inf')  # initialize the max value
      local_alpha = float(alpha)
      local_beta = float(beta)
      for action in gameState.getLegalActions(0):
          v = max(v, self.value(gameState.generateSuccessor(0, action), depth, 1, local_alpha, local_beta))
          local_alpha = max(local_alpha, v)
          if local_alpha >= local_beta:
              return v

      return v

  def minValue(self, gameState, depth, ghostIndex, alpha, beta):
      v = float('inf')  # initialize the min value
      local_alpha = float(alpha)
      local_beta = float(beta)
      for action in gameState.getLegalActions(ghostIndex):
          if ghostIndex == gameState.getNumAgents() - 1:
              v = min(v, self.value(gameState.generateSuccessor(ghostIndex, action), depth + 1, 0, local_alpha, local_beta))  # to further depth
          else:
              v = min(v, self.value(gameState.generateSuccessor(ghostIndex, action), depth,
                                    ghostIndex + 1, local_alpha, local_beta))  # iterate through all the ghost agents
          local_beta = min(local_beta, v)
          if local_alpha >= local_beta:
              return v

      return v



class ExpectimaxAgent(MultiAgentSearchAgent):
  """
    Your expectimax agent (question 4)
  """

  def getAction(self, gameState):
    """
      Returns the expectimax action using self.depth and self.evaluationFunction

      All ghosts should be modeled as choosing uniformly at random from their
      legal moves.
    """
    "*** YOUR CODE HERE ***"
    # at depth 0 & agentIndex = 0
    v = float('-inf')
    chooseAction = gameState.getLegalActions(0)[0]
    for action in gameState.getLegalActions(0):
        if self.value(gameState.generateSuccessor(0, action), 0, 1) > v:
            v = self.value(gameState.generateSuccessor(0, action), 0, 1)
            chooseAction = action

    return chooseAction

  def value(self, gameState, depth, agentIndex):
      if gameState.isWin() or gameState.isLose() or depth == self.depth:  # chech if it's a terminal state
          return self.evaluationFunction(gameState)

      if agentIndex == 0:
          return self.maxValue(gameState, depth, agentIndex)
      else:
          return self.expectValue(gameState, depth, agentIndex)

  def maxValue(self, gameState, depth, agentIndex):
      v = float('-inf')  # initialize the max value
      for action in gameState.getLegalActions(0):
          v = max(v, self.value(gameState.generateSuccessor(0, action), depth, 1))

      return v

  def expectValue(self, gameState, depth, ghostIndex):

      expectation = 0
      legalActions = gameState.getLegalActions(ghostIndex)

      for action in legalActions:
          if ghostIndex == gameState.getNumAgents() - 1:
              expectation += self.value(gameState.generateSuccessor(ghostIndex, action), depth + 1, 0)

          else:
              expectation += self.value(gameState.generateSuccessor(ghostIndex, action), depth,
                                    ghostIndex + 1)

      return expectation / len(legalActions)

def getClusterSize(foodPlot, startPos):

    if not foodPlot[startPos[0]][startPos[1]]:
        return 0

    m = len(foodPlot[0])
    n = len(foodPlot)

    count = 1
    explored = [[False] * m] * n
    explored[startPos[0]][startPos[1]] = True
    nextQueue = [startPos]

    def register(x, y):
        explored[x][y] = True
        nextQueue.append((x, y))

    while nextQueue:
        x, y = nextQueue.pop()

        if x - 1 >= 0:
            if y - 1 >= 0:
                if not explored[x - 1][y - 1] and foodPlot[x - 1][y - 1]:
                    register(x - 1, y - 1); count += 1
            if not explored[x - 1][y] and foodPlot[x - 1][y]:
                register(x - 1, y); count += 1
            if y + 1 < n:
                if not explored[x - 1][y + 1] and foodPlot[x - 1][y + 1]:
                    register(x - 1, y + 1); count += 1

        if y - 1 >= 0:
            if not explored[x][y - 1] and foodPlot[x][y - 1]:
                register(x, y - 1); count += 1
        if y + 1 < n:
            if not explored[x][y + 1] and foodPlot[x][y + 1]:
                register(x, y + 1);
                count += 1

        if n + 1 < m:
            if y - 1 >= 0:
                if not explored[x + 1][y - 1] and foodPlot[x + 1][y - 1]:
                    register(x + 1, y - 1); count += 1
            if not explored[x + 1][y] and foodPlot[x + 1][y]:
                register(x + 1, y); count += 1
            if y + 1 < n:
                if not explored[x + 1][y + 1] and foodPlot[x + 1][y + 1]:
                    register(x + 1, y + 1); count += 1

    return count

def betterEvaluationFunction(currentGameState):
  """
    Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
    evaluation function (question 5).

    DESCRIPTION: forced random tie-breaking by adding small fluctuation
  """
  "*** YOUR CODE HERE ***"

  pos = currentGameState.getPacmanPosition()
  food = currentGameState.getFood()
  ghostStates = currentGameState.getGhostStates()
  scaredTimes = [ghostState.scaredTimer for ghostState in ghostStates]

  closeFoodWeight = 10
  remainingFoodWeight = -10
  ghostFleeWeight = -1
  ghostHuntWeight = 10

  closeFoodScore = 0
  remainingFoodScore = 0
  ghostFleeScore = 0
  ghostHuntScore = 0

  for foodpos in food.asList():
      remainingFoodScore += 1
      closeFoodScore = min(closeFoodScore, util.manhattanDistance(pos, foodpos))

  for i, ghostState in enumerate(ghostStates):
      if scaredTimes[i] > 1:
          ghostHuntScore += 1 / max(util.manhattanDistance(pos, ghostState.getPosition()), 1)
      else:
          if util.manhattanDistance(pos, ghostState.getPosition()):
              ghostFleeScore += 1 / util.manhattanDistance(pos, ghostState.getPosition())
          else:
              ghostFleeScore += 100000

  import random

  return closeFoodWeight * closeFoodScore + remainingFoodWeight * remainingFoodScore + ghostFleeWeight * ghostFleeScore + ghostHuntWeight * ghostHuntScore + random.uniform(0, 0.0001)

# Abbreviation
better = betterEvaluationFunction

class ContestAgent(MultiAgentSearchAgent):
  """
    Your agent for the mini-contest
    Using depth-3 ExpectimaxAgent that's attraced to food
  """

  def getAction(self, gameState):
    """
      Returns an action.  You can use any method you want and search to any depth you want.
      Just remember that the mini-contest is timed, so you have to trade off speed and computation.

      Ghosts don't behave randomly anymore, but they aren't perfect either -- they'll usually
      just make a beeline straight towards Pacman (or away from him if they're scared!)
    """
    "*** YOUR CODE HERE ***"
    legalActions = gameState.getLegalActions(0)
    chooseAction = legalActions[0]
    v = float('-inf')

    for action in gameState.getLegalActions(0):
        if action != Directions.STOP:
            if self.value(gameState.generateSuccessor(0, action), 0, 1) > v:
                v = self.value(gameState.generateSuccessor(0, action), 0, 1)
                chooseAction = action

    return chooseAction

  def value(self, gameState, depth, agentIndex):
    if gameState.isWin() or gameState.isLose() or depth == 3:  # chech if it's a terminal state
      closeFoodScore = float('inf')
      for foodpos in gameState.getFood().asList():
        closeFoodScore = min(closeFoodScore, util.manhattanDistance(gameState.getPacmanPosition(), foodpos))

          
      return self.evaluationFunction(gameState) + random.uniform(0, 0.0001) + 12/closeFoodScore 

    if agentIndex == 0:
        return self.maxValue(gameState, depth, agentIndex)
    else:
        return self.expectValue(gameState, depth, agentIndex)

  def maxValue(self, gameState, depth, agentIndex):
    v = float('-inf')  # initialize the max value
    for action in gameState.getLegalActions(0):
        v = max(v, self.value(gameState.generateSuccessor(0, action), depth, 1))

    return v

  def expectValue(self, gameState, depth, ghostIndex):

    expectation = 0
    legalActions = gameState.getLegalActions(ghostIndex)

    for action in legalActions:
        if ghostIndex == gameState.getNumAgents() - 1:
            expectation += self.value(gameState.generateSuccessor(ghostIndex, action), depth + 1, 0)

        else:
            expectation += self.value(gameState.generateSuccessor(ghostIndex, action), depth,
                                      ghostIndex + 1)

    return expectation / len(legalActions)


 