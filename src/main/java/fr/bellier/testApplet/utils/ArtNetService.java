/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package fr.bellier.testApplet.utils;

import fr.bellier.testApplet.entities.Box;
import java.util.List;

/**
 *
 * @author bruno
 */
public class ArtNetService {

    public int[] colorToByteArray(List<Box> boxes) {
        int[] dmx = new int[(3 * boxes.size())];
        for (Box box : boxes) {
            int i = box.getIndex();
            dmx[i * 3] = box.getRed();
            dmx[i * 3 + 1] = box.getGreen();
            dmx[i * 3 + 2] = box.getBlue();
        }
        return dmx;
    }

}
