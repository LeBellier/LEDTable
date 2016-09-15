/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package fr.bellier.testApplet;

import fr.bellier.testApplet.entities.Box;
import java.awt.Color;
import java.util.LinkedList;
import java.util.List;

/**
 *
 * @author bruno
 */
public class TableGame extends java.util.Observable {

    private final List<Box> boxes = new LinkedList<Box>();
    protected final int maxRow = 1;
    protected final int maxCol = 12;
    protected static TableGame game;

    public TableGame() {

        for (int i = 0; i < maxRow * maxCol; i++) {
            boxes.add(new Box(i, Color.CYAN));
        }
        Application_1 app = new Application_1(maxRow, maxCol, this);
        addObserver(app);
        app.setVisible(true);
        ArtNetManager artNetManager = new ArtNetManager();
        addObserver(artNetManager);
        artNetManager.initArtNetServer();
    }

    int getSize() {
        return boxes.size();
    }

    void setSquare(int index, Color c, Boolean sendAfter) {
        for (Box box : boxes) {
            if (box.getIndex() == index) {
                box.setColor(c);
            }
        }

        if (sendAfter) {
            setChanged();
            notifyObservers(boxes);
        }
    }

    void setAllSquare(Color c) {
        for (Box box : boxes) {
            box.setColor(c);
        }
        setChanged();
        notifyObservers(boxes);
    }
}
