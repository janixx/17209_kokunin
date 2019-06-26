package ru.nsu.fit.g17209.kokunin.task2.model;

import org.junit.Test;

import java.awt.*;

import static org.junit.Assert.*;

public class BoardTest {
    @Test(expected = IllegalArgumentException.class)
    public void testNewGame() throws IllegalArgumentException {
        Board b = new Board();
        b.newGame();
        
        assertFalse(b.isCellEmpty(3,3));
        assertTrue(b.isCellEmpty(1,1));
    
        Point p = new Point(2,3);
        b.move(p);
        
        assertSame(4, b.getScore(Color.BLACK));
        assertSame(1, b.getScore(Color.WHITE));
        assertTrue(b.isCellLocked(p.x, p.y));
        assertTrue(b.isThisColor(p.x, p.y, Color.BLACK));
        assertFalse(b.isAnotherColor(p.x, p.y, Color.BLACK));
        assertFalse(b.isAnotherColor(7, 7, Color.BLACK));
        
        p.setLocation(2,4);
        b.move(p);
        assertEquals(b.getScore(Color.WHITE), b.getScore(Color.BLACK));
        
        p.setLocation(3,5);
        b.move(p);
        p.setLocation(2,6);
        b.move(p);
        p.setLocation(1,5);
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
        p.setLocation(3,7);
        b.move(p);
        p.setLocation(4,5);
        b.move(p);
        p.setLocation(5,5);
        b.move(p);
        p.setLocation(3,2);
        b.move(p);
        p.setLocation(2,2);
        b.move(p);
        p.setLocation(1,6);
        b.move(p);
        
        assertSame(1, b.getScore(Color.BLACK));
        assertSame(Color.WHITE, b.getPlayerColor());
        
        p.setLocation(0,7);
        b.move(p);
        assertEquals(1, b.isGameFinish());
        assertEquals(22, b.getScore(Color.BLACK));
        assertEquals(0, b.getScore(Color.WHITE));
        assertFalse(b.isThisColor(7,0, Color.BLACK));
        assertFalse(b.isThisColor(7,1, Color.BLACK));
        assertFalse(b.isThisColor(7,2, Color.BLACK));
        assertFalse(b.isThisColor(7,3, Color.BLACK));
        assertFalse(b.isThisColor(7,4, Color.BLACK));
        assertFalse(b.isThisColor(7,5, Color.BLACK));
        assertFalse(b.isThisColor(7,6, Color.BLACK));
        assertFalse(b.isThisColor(7,7, Color.BLACK));
        assertFalse(b.isThisColor(0,0, Color.BLACK));
        
        
        p.setLocation(8,8);
        b.move(p);
    }
}