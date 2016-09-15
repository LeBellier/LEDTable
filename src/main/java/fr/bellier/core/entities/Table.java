package fr.bellier.core.entities;

import java.awt.Color;
import java.util.LinkedList;
import java.util.List;

/**
 *
 * @author LeBellier
 */
public class Table extends java.util.Observable {

    private final List<Box> boxes = new LinkedList<Box>();
    protected final int nbRows = 1;
    protected final int nbColumns = 12;
    protected static Table game;

    public Table() {

        for (int i = 0; i < nbRows * nbColumns; i++) {
            boxes.add(new Box(i, Color.CYAN));
        }
    }

    public int getSize() {
        return boxes.size();
    }

    /**
     * This method change 0 or 1 Box, when you have finish to modify boxes, do
     * .notifyObservers()
     *
     * @param index
     * @param c
     */
    public void setBox(int index, Color c) {
        for (Box box : boxes) {
            if (box.getIndex() == index) {
                box.setColor(c);
                setChanged();
            }
        }
    }

    public void setAllBoxes(Color c) {
        for (Box box : boxes) {
            box.setColor(c);
        }
        setChanged();
        notifyObservers(boxes);
    }
}
