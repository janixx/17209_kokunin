package ru.nsu.fit.g17209.kokunin.task2.model;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import ru.nsu.fit.g17209.kokunin.task2.view.ViewCell;

import java.awt.*;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;

import static org.junit.Assert.*;
import static ru.nsu.fit.g17209.kokunin.task2.model.Board.SIZE;
import static ru.nsu.fit.g17209.kokunin.task2.model.Color.WHITE;
import static ru.nsu.fit.g17209.kokunin.task2.model.Color.BLACK;

public class BoardTest {
    Board b = new Board();
    Point p = new Point(2,3);
    
    @Before
    public void setUpBeforTest() {
        b.newGame();
        p.setLocation(2,3);
        b.move(p);
        p.setLocation(2,4);
        b.move(p);
        p.setLocation(3,5);
        b.move(p);
        p.setLocation(2,6);
        b.move(p);
        p.setLocation(1,5);
        b.move(p);
        p.setLocation(4,2);
        b.move(p);
        p.setLocation(5,3);
        b.move(p);
        p.setLocation(0,6);
        b.move(p);
        p.setLocation(2,5);
        b.move(p);
        p.setLocation(6,3);
        b.move(p);
        p.setLocation(3, 6);
        b.move(p);
        p.setLocation(2,2);
        b.move(p);
        p.setLocation(1,6);
        b.move(p);
        p.setLocation(3,7);
        b.move(p);
        p.setLocation(1,4);
        b.move(p);
        p.setLocation(0,5);
        b.move(p);
        p.setLocation(4,6);
        b.move(p);
//        p.setLocation(5,6);
//        b.move(p);
    }
    
    @After
    public void tearDownAfterTest() {
        b.newGame();
    }
    
    @Test
    public void addBoardListener() {
        b.addBoardListener(new PropertyChangeListener() {
            @Override
            public void propertyChange(PropertyChangeEvent evt) {
                return;
            }
        });
        b.addBoardListener(new PropertyChangeListener() {
            @Override
            public void propertyChange(PropertyChangeEvent evt) {
                return;
            }
        });
    
        p.setLocation(5,6);
        b.move(p);
    }
    
    @Test(expected = NullPointerException.class)
    public void addCellListeners() {
        b.addCellListeners(new ViewCell[SIZE][SIZE]);
    }
    
    @Test(expected = IllegalArgumentException.class)
    public void move() throws IllegalArgumentException {
        p.setLocation(8,8);
        b.move(p);
    }
    
    @Test
    public void isGameFinish() {
        assertSame(-1, b.isGameFinish());
        p.setLocation(5,6);
        b.move(p);
        assertSame(1, b.isGameFinish());
    }
    
    @Test
    public void getScore() {
        assertSame(4, b.getScore(BLACK));
        assertSame(17, b.getScore(WHITE));
        p.setLocation(5,6);
        b.move(p);
        assertSame(22, b.getScore(WHITE));
        assertSame(0, b.getScore(BLACK));
    }
    
    @Test
    public void isThisColor() {
        assertTrue(b.isThisColor(2,2, WHITE));
        assertTrue(b.isThisColor(2,3, WHITE));
        assertTrue(b.isThisColor(2,4, WHITE));
        assertTrue(b.isThisColor(2,5, WHITE));
        assertTrue(b.isThisColor(1,5, WHITE));
        assertTrue(b.isThisColor(0,5, WHITE));
        assertTrue(b.isThisColor(0,6, WHITE));
        assertTrue(b.isThisColor(3,5, WHITE));
        assertTrue(b.isThisColor(3,4, WHITE));
        assertTrue(b.isThisColor(3,3, WHITE));
        assertTrue(b.isThisColor(4,2, WHITE));
        assertTrue(b.isThisColor(1,6, BLACK));
        assertTrue(b.isThisColor(2,6, BLACK));
        assertTrue(b.isThisColor(3,6, BLACK));
        assertTrue(b.isThisColor(4,6, BLACK));
        p.setLocation(5,6);
        b.move(p);
        assertFalse(b.isThisColor(5,6, BLACK));
    }
    
    @Test
    public void isAnotherColor() {
        assertTrue(b.isAnotherColor(2,2, BLACK));
        assertTrue(b.isAnotherColor(2,3, BLACK));
        assertTrue(b.isAnotherColor(2,4, BLACK));
        assertTrue(b.isAnotherColor(2,5, BLACK));
        assertTrue(b.isAnotherColor(1,5, BLACK));
        assertTrue(b.isAnotherColor(0,5, BLACK));
        assertTrue(b.isAnotherColor(0,6, BLACK));
        assertTrue(b.isAnotherColor(3,5, BLACK));
        assertTrue(b.isAnotherColor(3,4, BLACK));
        assertTrue(b.isAnotherColor(3,3, BLACK));
        assertTrue(b.isAnotherColor(4,2, BLACK));
        assertTrue(b.isAnotherColor(1,6, WHITE));
        assertTrue(b.isAnotherColor(2,6, WHITE));
        assertTrue(b.isAnotherColor(3,6, WHITE));
        assertTrue(b.isAnotherColor(4,6, WHITE));
        p.setLocation(5,6);
        b.move(p);
        assertFalse(b.isAnotherColor(5,6, WHITE));
    }
    
    @Test
    public void isCellEmpty() {
        assertFalse(b.isCellEmpty(2,2));
        assertFalse(b.isCellEmpty(2,3));
        assertFalse(b.isCellEmpty(2,4));
        assertFalse(b.isCellEmpty(2,5));
        assertFalse(b.isCellEmpty(1,5));
        assertFalse(b.isCellEmpty(0,5));
        assertFalse(b.isCellEmpty(0,6));
        assertFalse(b.isCellEmpty(3,5));
        assertFalse(b.isCellEmpty(3,4));
        assertFalse(b.isCellEmpty(3,3));
        assertFalse(b.isCellEmpty(4,2));
        assertFalse(b.isCellEmpty(1,6));
        assertFalse(b.isCellEmpty(2,6));
        assertFalse(b.isCellEmpty(3,6));
        assertFalse(b.isCellEmpty(4,6));
        
        p.setLocation(5,6);
        b.move(p);
        assertFalse(b.isCellEmpty(5,6));
        
        assertTrue(b.isCellEmpty(7,0));
        assertTrue(b.isCellEmpty(6,0));
        assertTrue(b.isCellEmpty(5,0));
    }
    
    @Test
    public void isCellLocked() {
        assertTrue(b.isCellLocked(2,2));
        assertTrue(b.isCellLocked(2,3));
        assertTrue(b.isCellLocked(2,4));
        assertTrue(b.isCellLocked(2,5));
        assertTrue(b.isCellLocked(1,5));
        assertTrue(b.isCellLocked(0,5));
        assertTrue(b.isCellLocked(0,6));
        assertTrue(b.isCellLocked(3,5));
        assertTrue(b.isCellLocked(3,4));
        assertTrue(b.isCellLocked(3,3));
        assertTrue(b.isCellLocked(4,2));
        assertTrue(b.isCellLocked(1,6));
        assertTrue(b.isCellLocked(2,6));
        assertTrue(b.isCellLocked(3,6));
        assertTrue(b.isCellLocked(4,6));
        assertFalse(b.isCellLocked(5,6));
        assertFalse(b.isCellLocked(5,7));
        assertFalse(b.isCellLocked(4,7));
        assertFalse(b.isCellLocked(2,7));
        assertFalse(b.isCellLocked(1,7));
        assertFalse(b.isCellLocked(0,7));
    }
    
    @Test
    public void getPlayerColor() {
        assertSame(WHITE, b.getPlayerColor());
        p.setLocation(5,6);
        b.move(p);
        assertSame(WHITE, b.getPlayerColor());
    }
}