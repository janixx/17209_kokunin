package ru.nsu.fit.g17209.kokunin.task2.model;

import org.junit.Test;

import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;

import static org.junit.Assert.*;

public class CellTest {
    class MyListener implements PropertyChangeListener {
        int counter = 0;
        @Override
        public void propertyChange(PropertyChangeEvent evt) {
            ++counter;
        }
        
        int getCount() { return counter; }
    }
    
    @Test
    public void testIsEmpty() {
        Cell cell = new Cell();
    
        assertTrue(cell.isLocked());
        assertTrue(cell.isEmpty());
        assertFalse(cell.isBlack());
        assertFalse(cell.isWhite());
        
        MyListener property = new MyListener(),
                change = new MyListener();
    
        cell.addListener(property);
        cell.addListener(change);
        
        cell.setLocked(false);
        cell.removeListener(property);
        
        cell.setWhite();
        cell.removeListener(change);
        
        assertSame(1, property.getCount());
        assertSame(2, change.getCount());
        assertTrue(cell.isLocked());
        assertFalse(cell.isEmpty());
        assertTrue(cell.isWhite());
    }
}