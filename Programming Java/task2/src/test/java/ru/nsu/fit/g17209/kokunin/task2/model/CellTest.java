package ru.nsu.fit.g17209.kokunin.task2.model;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;

import static org.junit.Assert.*;
import static ru.nsu.fit.g17209.kokunin.task2.model.Color.WHITE;
import static ru.nsu.fit.g17209.kokunin.task2.model.Color.BLACK;


public class CellTest {
    Cell cell = new Cell();
    
    class Listener implements PropertyChangeListener {
        int counter = 0;
        @Override
        public void propertyChange(PropertyChangeEvent evt) {
            counter++;
        }
        
        public int getCountChanges() {
            return counter;
        }
    }
    
    @Before
    public void setUpBeforTest() {
        cell.clear();
        cell.setLocked(false);
    }
    
    @Test
    public void addListener() {
        Listener first = new Listener();
        cell.addListener(first);
        cell.setWhite();
        cell.setBlack();
        
        Listener second = new Listener();
        cell.addListener(second);
        cell.setLocked(true);
        
        assertSame(5, first.getCountChanges());
        assertSame(2, second.getCountChanges());
        
        cell.removeListener(first);
        cell.setLocked(false);
        cell.removeListener(second);
    
        assertSame(5, first.getCountChanges());
        assertSame(3, second.getCountChanges());
    }
    
    @Test
    public void setLocked() {
        assertFalse(cell.isLocked());
        cell.setLocked(true);
        assertTrue(cell.isLocked());
    }
    
    @Test
    public void setColor() {
        assertFalse(cell.isWhite());
        assertFalse(cell.isBlack());
        assertTrue(cell.isEmpty());
        
        cell.setColor(BLACK);
        assertFalse(cell.isWhite());
        assertTrue(cell.isBlack());
        
        cell.setColor(WHITE);
        assertTrue(cell.isWhite());
        assertFalse(cell.isBlack());
    }
    
    @Test
    public void setWhite() {
        assertFalse(cell.isWhite());
        assertFalse(cell.isBlack());
        assertTrue(cell.isEmpty());
        
        cell.setWhite();
        assertTrue(cell.isWhite());
        assertFalse(cell.isBlack());
    }
    
    @Test
    public void setBlack() {
        assertFalse(cell.isWhite());
        assertFalse(cell.isBlack());
        assertTrue(cell.isEmpty());
    
        cell.setBlack();
        assertTrue(cell.isBlack());
        assertFalse(cell.isWhite());
    }
    
    @Test
    public void clear() {
        cell.setWhite();
        assertTrue(cell.isWhite());
        assertFalse(cell.isBlack());
        
        cell.setLocked(true);
        assertTrue(cell.isLocked());
        assertFalse(cell.isEmpty());
        
        cell.clear();
        assertTrue(cell.isLocked());
        assertTrue(cell.isEmpty());
    
    }
}