/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package fr.bellier.randomApp;

import fr.bellier.core.entities.Table;
import java.awt.Color;
import java.util.LinkedList;
import java.util.List;

/**
 *
 * @author LeBellier
 */
public class RandomGame {

    private static RandomGame game;

    private final List<Integer> availableBoxes = new LinkedList<Integer>();
    private final Table table = new Table();

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(RandomGame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(RandomGame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(RandomGame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(RandomGame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            @Override
            public void run() {
                RandomGame.getSingleton();
            }
        });
    }

    public static RandomGame getSingleton() {
        if (game == null) {
            game = new RandomGame();
        }
        return game;
    }

    RandomGame() {
        restart();
    }

    /**
     *
     * @return index of the chosen square
     */
    public int nextStep() {

        NextStepThread nextStepThread = new NextStepThread();
        nextStepThread.start();
        return 1;
    }

    public void restart() {
        table.setAllBoxes(Color.BLACK);
        availableBoxes.clear();
        for (int i = 0; i < table.getSize(); i++) {
            availableBoxes.add(i);
        }
    }

    class NextStepThread extends Thread {

        @Override
        public void run() {
            int higher = availableBoxes.size();
            int idWinnerBox = (int) (Math.random() * higher);
            int nbIntermediateBox = (int) (Math.random() * 10);
            for (int i = 0; i < nbIntermediateBox + 10; i++) {
                int idCurrentBox = (int) (Math.random() * higher);
                table.setBox(availableBoxes.get(idCurrentBox), Color.green);
                table.notifyObservers();
                try {
                    Thread.sleep(50);
                } catch (InterruptedException ex) {
                    Thread.currentThread().interrupt();
                }
                table.setBox(availableBoxes.get(idCurrentBox), Color.black);
            }
            table.setBox(availableBoxes.get(idWinnerBox), Color.red);
            table.notifyObservers();
            availableBoxes.remove(idWinnerBox);
        }
    }
}
